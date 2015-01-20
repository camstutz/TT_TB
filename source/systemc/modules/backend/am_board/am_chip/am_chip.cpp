/*!
 * @file am_chip.cpp
 * @author Christian Amstutz
 * @date November 15, 2014
 *
 * @brief File containing the implementation of the AM board.
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_chip.hpp"

// *****************************************************************************

am_chip::am_chip(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        init_ev("init_ev"),
        write_en(NR_DETECTOR_LAYERS, "write_en"),
        pattern_inputs(NR_DETECTOR_LAYERS, "pattern_input"),
        data_ready("data_ready"),
        road_output("road_output"),
        output_roads_buffer_empty("output_roads_buffer_empty"),
        process_roads_sig("process_roads_sig"),
        write_roads_sig("write_roads_sig"),
        output_data_ready_no_delay("output_data_ready_no_delay"),
        output_road_no_delay("output_road_no_delay"),
        detected_roads_buffer("detected_roads_buffer"),
        fsm("FSM"),
        latency_correction_data_ready("latency_correction_data_ready"),
        latency_correction_road("latency_correction_road")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_hits);
        sensitive << clk.pos();
    SC_THREAD(detect_roads);
        sensitive << process_roads_sig.posedge_event();
    SC_THREAD(write_roads);
        sensitive << clk.pos() << write_roads_sig.posedge_event();
    SC_THREAD(check_detected_road_buffer);
        sensitive << detected_roads_buffer.data_written_event()
                << detected_roads_buffer.data_read_event();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    fsm.clk.bind(clk);
    fsm.write_en.bind(write_en);
    fsm.road_buffer_empty.bind(output_roads_buffer_empty);
    fsm.process_roads.bind(process_roads_sig);
    fsm.write_roads.bind(write_roads_sig);

    latency_correction_data_ready.clk.bind(clk);
    latency_correction_data_ready.input.bind(output_data_ready_no_delay);
    latency_correction_data_ready.delayed.bind(data_ready);

    latency_correction_road.clk.bind(clk);
    latency_correction_road.input.bind(output_road_no_delay);
    latency_correction_road.delayed.bind(road_output);

    initialize_patterns();
    clear_match_table();

    match_table.resize(nr_pattern);
    std::vector<std::vector<bool> >::iterator match_table_it = match_table.begin();
    for(; match_table_it != match_table.end(); ++match_table_it)
    {
        match_table_it->resize(NR_DETECTOR_LAYERS);
    }

    return;
}

// *****************************************************************************
void am_chip::process_incoming_hits()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < NR_DETECTOR_LAYERS; ++layer)
        {
            if (write_en[layer])
            {
                pattern_t pattern = pattern_inputs[layer].read();

                std::cout << pattern_bank[layer].size() << "/" << pattern_bank[layer].count(pattern.to_uint()) << std::endl;

                std::pair<lay_pattern_bank_t::iterator, lay_pattern_bank_t::iterator> road_addresses = pattern_bank[layer].equal_range(pattern.to_uint());
                lay_pattern_bank_t::iterator road_addr_it = road_addresses.first;

                while (road_addr_it != road_addresses.second)
                {
                    unsigned int road_addr = road_addr_it->second.to_uint();
                    match_table[road_addr][layer] = true;
                    ++road_addr_it;
                }
                print_match_table();
            }
        }
    }

}

// *****************************************************************************
void am_chip::detect_roads()
{
    while (1)
    {
        wait();

        unsigned int road_nr = 0;

        std::vector<std::vector<bool> >::iterator match_line_it = match_table.begin();
        for (; match_line_it != match_table.end(); ++match_line_it)
        {
            unsigned int road_hits = 0;
            std::vector<bool>::iterator match_position_it = match_line_it->begin();
            for (; match_position_it != match_line_it->end(); ++match_position_it)
            {
                if (*match_position_it)
                {
                    ++road_hits;
                }
            }

            if (road_hits >= AM_HITS_PER_ROAD_THRESHOLD)
            {
                detected_roads_buffer.write(road_addr_t(road_nr));
            }

            ++road_nr;
        }

        clear_match_table();
    }

}

// *****************************************************************************
void am_chip::write_roads()
{
    while (1)
    {
        wait();

        output_data_ready_no_delay.write(false);

        if (write_roads_sig)
        {
            if (!output_roads_buffer_empty)
            {
                road_addr_t road = detected_roads_buffer.read();
                output_data_ready_no_delay.write(true);
                output_road_no_delay.write(road);
            }
        }
    }

}

// *****************************************************************************
void am_chip::check_detected_road_buffer()
{
    while (1)
    {
        if (detected_roads_buffer.num_available() == 0)
        {
            output_roads_buffer_empty.write(true);
        }
        else
        {
            output_roads_buffer_empty.write(false);
        }

        wait();
    }
}

// *****************************************************************************
void am_chip::print_pattern_bank()
{
	std::cout << "Pattern Bank:\n";

	std::vector<std::multimap<unsigned int, road_addr_t>::iterator> pattern_it_vec;
	std::vector<std::multimap<unsigned int, road_addr_t>::iterator> pattern_it_end_vec;

	// Initialize all vector iterators
    std::vector<lay_pattern_bank_t>::iterator layer_it = pattern_bank.begin();
    for (; layer_it != pattern_bank.end(); ++layer_it)
    {
    	pattern_it_vec.push_back(layer_it->begin());
    	pattern_it_end_vec.push_back(layer_it->end());
	}

    for (unsigned int pattern_nr = 0; pattern_nr < pattern_bank[0].size(); ++pattern_nr)
    {
    	std::vector<std::multimap<unsigned int, road_addr_t>::iterator>::iterator pattern_it_it = pattern_it_vec.begin();

    	std::cout << std::hex << (*pattern_it_it)->first << " : ";
		std::cout << std::hex << (*pattern_it_it)->second;
		*pattern_it_it = ++(*pattern_it_it);
		++pattern_it_it;
    	for (; pattern_it_it != pattern_it_vec.end(); ++pattern_it_it)
    	{
    		std::cout << "," << std::hex << (*pattern_it_it)->second;
    		*pattern_it_it = ++(*pattern_it_it);
    	}
    	std::cout << "\n";
    }

    return;
}

// *****************************************************************************
void am_chip::print_match_table()
{
	std::cout << "Match Table:\n";

    std::vector<std::vector<bool> >::iterator match_line_it = match_table.begin();
    for (; match_line_it != match_table.end(); ++match_line_it)
    {
        std::vector<bool>::iterator match_position_it = match_line_it->begin();
        for (; match_position_it != match_line_it->end(); ++match_position_it)
    	{
    		if (*match_position_it)
          	{
    			std::cout << "*,";
            }
            else
            {
            	std::cout << " ,";
            }
        }
        std::cout << "\n";
	}
}

// *****************************************************************************
void am_chip::initialize_patterns()
{
    pattern_bank.resize(NR_DETECTOR_LAYERS);

    for (unsigned int layer=0; layer<NR_DETECTOR_LAYERS; ++layer)
    {
    	if (layer < NR_DETECTOR_MPA_LAYERS)
    	{
    		for (unsigned int pat_nr=0; pat_nr<nr_pattern; ++pat_nr)
    		{
    			pattern_t pattern;
    			pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr%256)) );
    			pattern_bank[layer].insert(std::pair<unsigned int, road_addr_t>(pat_nr, pattern.to_uint()) );
    		}
        }
    	// CBC Layers
    	else
    	{
    		for (unsigned int pat_nr=0; pat_nr<256; ++pat_nr)
    		{
    			pattern_t pattern;
    			pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr)) );
    			pattern_bank[layer].insert(std::pair<unsigned int, road_addr_t>(pat_nr, pattern.to_uint()) );
    		}
    		for (unsigned int pat_nr=256; pat_nr<512; ++pat_nr)
    		{
    			pattern_t pattern;
    			pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr%256+1)) );
    			pattern_bank[layer].insert(std::pair<unsigned int, road_addr_t>(pat_nr, pattern.to_uint()) );
    		}
    		for (unsigned int pat_nr=512; pat_nr<768; ++pat_nr)
    		{
    			pattern_t pattern;
    			pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr%256+2)) );
    			pattern_bank[layer].insert(std::pair<unsigned int, road_addr_t>(pat_nr, pattern.to_uint()) );
    		}
    		for (unsigned int pat_nr=768; pat_nr<1024; ++pat_nr)
    		{
    			pattern_t pattern;
    			pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr%256-1)) );
    			pattern_bank[layer].insert(std::pair<unsigned int, road_addr_t>(pat_nr, pattern.to_uint()) );
    		}
    		for (unsigned int pat_nr=1024; pat_nr<1280; ++pat_nr)
    		{
    			pattern_t pattern;
    			pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr%256-2)) );
    			pattern_bank[layer].insert(std::pair<unsigned int, road_addr_t>(pat_nr, pattern.to_uint()) );
    		}
    	}
    }

    return;
}

// *****************************************************************************
void am_chip::clear_match_table()
{
    std::vector<std::vector<bool> >::iterator match_line_it = match_table.begin();
    for (; match_line_it != match_table.end(); ++match_line_it)
    {
        std::vector<bool>::iterator match_position_it = match_line_it->begin();
        for (; match_position_it != match_line_it->end(); ++match_position_it)
        {
            *match_position_it = false;
        }
    }

    return;
}
