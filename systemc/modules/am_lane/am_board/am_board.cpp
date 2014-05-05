/*!
 * @file am_board.cpp
 * @author Christian Amstutz
 * @date May 5, 2014
 *
 * @brief File containing the implementation of the AM board.
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_board.hpp"

// *****************************************************************************

am_board::am_board(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        init_ev("init_ev"),
        write_en(NR_DETECTOR_LAYERS, "write-en"),
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
    fsm.rst.bind(rst);
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

    return;
}

// *****************************************************************************
void am_board::process_incoming_hits()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < NR_DETECTOR_LAYERS; ++layer)
        {
            if (write_en[layer])
            {
                pattern_t pattern = pattern_inputs[layer].read();
                auto road_addresses = pattern_bank[layer].equal_range(pattern.to_uint());
                auto road_addr_it = road_addresses.first;

                while (road_addr_it != road_addresses.second)
                {
                    auto road_addr = road_addr_it->second.to_uint();
                    match_table[road_addr][layer] = true;
                    ++road_addr_it;
                }
            }
        }
    }

}

// *****************************************************************************
void am_board::detect_roads()
{
    while (1)
    {
        wait();

        unsigned int road_nr = 0;
        for (auto match_line : match_table)
        {
            unsigned int road_hits = 0;
            for (bool match_position : match_line)
            {
                if (match_position)
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
void am_board::write_roads()
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
void am_board::check_detected_road_buffer()
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
void am_board::print_pattern_bank()
{
	std::cout << "Pattern Banks:\n";
	for (auto pattern_bank_layer : pattern_bank)
	{
		for (auto pattern : pattern_bank_layer)
		{
			std::cout << pattern.first << ",";
		}
		std::cout << "\n";
	}
}

// *****************************************************************************
void am_board::print_match_table()
{
	std::cout << "Match Table:\n";
    for (auto match_line : match_table)
    {
    	for (bool hit_bit : match_line)
    	{
    		if (hit_bit)
          	{
    			std::cout << "*,";
            }
            else
            {
            	std::cout << " ,";
            }

            std::cout << "\n";
        }
	}
}

// *****************************************************************************
void am_board::initialize_patterns()
{
    for (auto& pattern_bank_layer: pattern_bank)
    {
        for (unsigned int pat_nr=0; pat_nr<nr_pattern; ++pat_nr)
        {
            pattern_t pattern;
            pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr)) );
            pattern_bank_layer.emplace(pattern.to_uint(), pat_nr);
        }
    }

    return;
}

// *****************************************************************************
void am_board::clear_match_table()
{
    for (auto& match_line : match_table)
    {
        for (bool& match_position : match_line)
        {
            match_position = false;
        }
    }

    return;
}
