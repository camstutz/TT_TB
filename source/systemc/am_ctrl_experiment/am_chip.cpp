/*!
 * @file am_chip.cpp
 * @author Christian Amstutz
 * @date Nov 14, 2014
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
        hit_inputs(LAYER_NUMBER, "hit_input"),
        road_output("road_output"),
        process_hits(LAYER_NUMBER, "process_hits"),
        roads_detected("roads_detected"),
        output_roads_buffer_empty("output_roads_buffer_empty"),
        process_roads_sig("process_roads_sig"),
        write_roads_sig("write_roads_sig"),
        output_data_ready_no_delay("output_data_ready_no_delay"),
        output_road_no_delay("output_road_no_delay"),
        detected_roads_buffer("detected_roads_buffer"),
        read_controller("read_controller"),
        write_controller("write_controller")
        //latency_correction_data_ready("latency_correction_data_ready"),
        //latency_correction_road("latency_correction_road")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_hits);
        hit_inputs.make_sensitive(sensitive);
    SC_THREAD(detect_roads);
        sensitive << process_roads_sig;
    SC_THREAD(write_roads);
        sensitive << clk.pos() << write_roads_sig.posedge_event();
    SC_THREAD(check_detected_road_buffer);
        sensitive << detected_roads_buffer.data_written_event()
                << detected_roads_buffer.data_read_event();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    read_controller.clk.bind(clk);
    read_controller.hit_inputs.bind(hit_inputs);
    read_controller.process_hits.bind(process_hits);
    read_controller.process_roads.bind(process_roads_sig);

    write_controller.clk.bind(clk);
    write_controller.roads_detected.bind(roads_detected);
    write_controller.road_input(detected_roads_buffer);
    write_controller.road_output(road_output);

//    latency_correction_data_ready.clk.bind(clk);
//    latency_correction_data_ready.input.bind(output_data_ready_no_delay);
//    latency_correction_data_ready.delayed.bind(data_ready);
//
//    latency_correction_road.clk.bind(clk);
//    latency_correction_road.input.bind(output_road_no_delay);
//    latency_correction_road.delayed.bind(road_output);

    initialize_patterns();
    clear_match_table();

    match_table.resize(nr_pattern);
    std::vector<std::vector<bool> >::iterator match_table_it = match_table.begin();
    for(; match_table_it != match_table.end(); ++match_table_it)
    {
        match_table_it->resize(LAYER_NUMBER);
    }

    return;
}

// *****************************************************************************
void am_chip::process_incoming_hits()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            if(process_hits[layer].read() & hit_inputs[layer].event())
            {
                pattern_t pattern = hit_inputs[layer].read();
                std::pair<lay_pattern_bank_t::iterator, lay_pattern_bank_t::iterator> road_addresses = pattern_bank[layer].equal_range(pattern);
                lay_pattern_bank_t::iterator road_addr_it = road_addresses.first;

                while (road_addr_it != road_addresses.second)
                {
                    unsigned int road_addr = road_addr_it->second;
                    match_table[road_addr][layer] = true;
                    ++road_addr_it;
                }
            }
        }
    }

}

// *****************************************************************************
void am_chip::detect_roads()
{
    roads_detected.write(false);

    while (1)
    {
        wait();
        if (process_roads_sig.read())
        {
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

            roads_detected.write(true);
            clear_match_table();
        }
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
	std::cout << "Pattern Banks:\n";

    std::vector<lay_pattern_bank_t>::iterator layer_it = pattern_bank.begin();
    for (; layer_it != pattern_bank.end(); ++layer_it)
    {
        std::multimap<unsigned int, road_addr_t>::iterator pattern_it = layer_it->begin();
		for (; pattern_it != layer_it->end(); ++pattern_it)
		{
			std::cout << pattern_it->first << ",";
		}
		std::cout << "\n";
	}
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

    return;
}

// *****************************************************************************
void am_chip::initialize_patterns()
{
    pattern_bank.resize(LAYER_NUMBER);

    std::vector<lay_pattern_bank_t>::iterator layer_it = pattern_bank.begin();
    for (; layer_it != pattern_bank.end(); ++layer_it)
    {
        for (unsigned int pat_nr=0; pat_nr<nr_pattern; ++pat_nr)
        {
            pattern_t pattern;
            pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr)) ).to_uint();
            layer_it->insert(std::pair<unsigned int, road_addr_t>(pat_nr, pattern) );
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
