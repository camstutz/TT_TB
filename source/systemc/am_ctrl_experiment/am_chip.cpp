/*!
 * @file am_chip.cpp
 * @author Christian Amstutz
 * @date December 8, 2014
 *
 * @brief File containing the implementation of the AM board.
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_chip.hpp"

// *****************************************************************************

am_chip::am_chip(sc_module_name _name, pattern_bank *p_bank) :
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
        write_controller("write_controller"),
        patterns(p_bank)
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
    roads_detected.write(false);

    // ----- Module instance / channel binding ---------------------------------

    write_controller.clk.bind(clk);
    write_controller.hit_inputs.bind(hit_inputs);
    write_controller.process_hits.bind(process_hits);
    write_controller.process_roads.bind(process_roads_sig);

    read_controller.clk.bind(clk);
    read_controller.roads_detected.bind(roads_detected);
    read_controller.road_input(detected_roads_buffer);
    read_controller.road_output(road_output);

//    latency_correction_data_ready.clk.bind(clk);
//    latency_correction_data_ready.input.bind(output_data_ready_no_delay);
//    latency_correction_data_ready.delayed.bind(data_ready);
//
//    latency_correction_road.clk.bind(clk);
//    latency_correction_road.input.bind(output_road_no_delay);
//    latency_correction_road.delayed.bind(road_output);

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
            if(process_hits[layer].read() & !hit_inputs[layer].read().is_opcode())
            {
                superstrip_stream stream_value = hit_inputs[layer].read();
                std::vector<pattern_bank::pattern_id_t> roads;
                roads = patterns->find_id(layer, stream_value.get_value());

                std::vector<pattern_bank::pattern_id_t>::iterator road_it = roads.begin();
                for (; road_it != roads.end(); ++road_it)
                {
                    match_table[*road_it].resize(LAYER_NUMBER);
                    match_table[*road_it][layer] = true;
                }
            }
        }
        std::cout << sc_time_stamp() << std::endl;
        print_match_table();
    }

}

// *****************************************************************************
void am_chip::detect_roads()
{
    while (1)
    {
        wait();
        if (process_roads_sig.read())
        {
            unsigned int road_nr = 0;

            std::map<pattern_bank::pattern_id_t, std::vector<bool> >::iterator match_line_it = match_table.begin();
            for (; match_line_it != match_table.end(); ++match_line_it)
            {
                unsigned int road_hits = 0;
                std::vector<bool>::iterator match_position_it = match_line_it->second.begin();
                for (; match_position_it != match_line_it->second.end(); ++match_position_it)
                {
                    if (*match_position_it)
                    {
                        ++road_hits;
                    }
                }

                if (road_hits >= AM_HITS_PER_ROAD_THRESHOLD)
                {
                    detected_roads_buffer.write(road_addr_t(match_line_it->first));
                }

                ++road_nr;
            }

            roads_detected.write(true);
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
	std::cout << "Pattern Banks:\n";
	patterns->print_pattern_bank();

	return;
}

// *****************************************************************************
void am_chip::print_match_table()
{
	std::cout << "Match Table:\n";

    std::map<pattern_bank::pattern_id_t, std::vector<bool> >::iterator match_line_it = match_table.begin();
    for (; match_line_it != match_table.end(); ++match_line_it)
    {
        std::cout << std::setw(8) << std::hex << match_line_it->first << ":";
        std::vector<bool>::iterator match_position_it = match_line_it->second.begin();
        for (; match_position_it != match_line_it->second.end(); ++match_position_it)
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
void am_chip::clear_match_table()
{
    match_table.clear();

    return;
}
