/*!
 * @file am_chip.cpp
 * @author Christian Amstutz
 * @date August 19, 2015
 *
 * @brief File containing the implementation of the AM board module.
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_chip.hpp"

// *****************************************************************************

am_chip::am_chip(sc_module_name _name, const am_chip_config configuration) :
        sc_module(_name),
        layer_nr(configuration.layer_nr),
        road_detection_threshold(configuration.road_detection_threshold),
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
        write_controller("write_controller", configuration.write_ctrl),
		delay_road_output("delay_road_output", configuration.latency_cycles),
        patterns()
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_hits);
        sensitive << hit_inputs;
    SC_THREAD(detect_roads);
        sensitive << process_roads_sig;
    SC_THREAD(check_detected_road_buffer);
        sensitive << detected_roads_buffer.data_written_event()
                  << detected_roads_buffer.data_read_event();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
    write_controller.clk.bind(clk);
    write_controller.hit_inputs.bind(hit_inputs);
    write_controller.process_hits.bind(process_hits);
    write_controller.process_roads.bind(process_roads_sig);

    read_controller.clk.bind(clk);
    read_controller.roads_detected.bind(roads_detected);
    read_controller.road_input.bind(detected_roads_buffer);
    read_controller.road_output.bind(road_output_sig);

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
    roads_detected.write(false);

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

                if ((road_hits == layer_nr) | (road_hits >= road_detection_threshold))
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
std::string am_chip::print_pattern_bank()
{
    std::stringstream output_stream;

	output_stream << "Pattern Banks:\n";
	output_stream << patterns->print_pattern_bank();

	return output_stream.str();
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
void am_chip::link_pattern_bank(pattern_bank* bank)
{
    patterns = bank;

    return;
}

// *****************************************************************************
void am_chip::clear_match_table()
{
    match_table.clear();

    return;
}
