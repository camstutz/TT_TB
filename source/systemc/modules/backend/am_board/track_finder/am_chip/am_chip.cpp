/*!
 * @file am_chip.cpp
 * @author Christian Amstutz
 * @date April 22, 2015
 *
 * @brief File containing the implementation of the AM board.
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_chip.hpp"

// *****************************************************************************

const unsigned int am_chip::layer_nr = NR_DETECTOR_LAYERS;

// *****************************************************************************

am_chip::am_chip(sc_module_name _name, pattern_bank *p_bank) :
        sc_module(_name),
        clk("clk"),
        hit_inputs(layer_nr, "hit_input"),
        road_output("road_output"),
        process_hits(layer_nr, "process_hits"),
        roads_detected("roads_detected"),
        output_roads_buffer_empty("output_roads_buffer_empty"),
        process_roads_sig("process_roads_sig"),
        write_roads_sig("write_roads_sig"),
		road_output_sig("road_output_sig"),
        detected_roads_buffer("detected_roads_buffer"),
        read_controller("read_controller"),
        write_controller("write_controller"),
		delay_road_output("delay_road_output"),
        patterns(p_bank)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_hits);
        hit_inputs.make_sensitive(sensitive);
    SC_THREAD(detect_roads);
        sensitive << process_roads_sig;
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
    read_controller.road_output(road_output_sig);

    delay_road_output.clk.bind(clk);
    delay_road_output.input.bind(road_output_sig);
    delay_road_output.delayed.bind(road_output);

    return;
}

// *****************************************************************************
void am_chip::process_incoming_hits()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < layer_nr; ++layer)
        {
            if(process_hits[layer].read() & !hit_inputs[layer].read().is_opcode())
            {
                superstrip_stream stream_value = hit_inputs[layer].read();
                std::vector<pattern_bank::pattern_id_t> roads;
                roads = patterns->find_id(layer, stream_value.get_value());

                std::vector<pattern_bank::pattern_id_t>::iterator road_it = roads.begin();
                for (; road_it != roads.end(); ++road_it)
                {
                    match_table[*road_it].resize(layer_nr, false);
                    match_table[*road_it][layer] = true;
                }
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
        if (process_roads_sig.read() == true)
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

                if ((road_hits == layer_nr) | (road_hits >= AM_HITS_PER_ROAD_THRESHOLD))
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
