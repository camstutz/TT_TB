/*!
 * @file road_processor.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "road_processor.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(road_processor);
#endif

// *****************************************************************************
road_processor::road_processor(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        road_input("road_input"),
        road_lookup("road_lookup"),
        found_pattern(LAYER_NUMBER, "found_pattern"),
        superstrip_lookup(LAYER_NUMBER, "superstrip_lookup"),
        hit_lookup_result(LAYER_NUMBER, "hit_lookup_result"),
        hit_output(LAYER_NUMBER, "hit_output"),
        command_buffer("command_buffer"),
		command_buffer_write_sig("command_buffer_write_sig"),
		command_buffer_delayed_sig("command_buffer_delayed_sig"),
		pattern_mem_delay_compensation("pattern_mem_delay_compensation")
{
	// ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_roads);
        sensitive << road_input;
    SC_THREAD(write_FIFO);
    	sensitive << command_buffer_delayed_sig;
    SC_THREAD(lookup_superstrips);
        sensitive << command_buffer.data_written_event();
        found_pattern.make_sensitive(sensitive);
    SC_THREAD(output_result);
        hit_lookup_result.make_sensitive(sensitive);

    // ----- Module channel/variable initialization ----------------------------
    pattern_mem_delay_compensation.clk.bind(clk);
    pattern_mem_delay_compensation.input.bind(command_buffer_write_sig);
    pattern_mem_delay_compensation.delayed.bind(command_buffer_delayed_sig);

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void road_processor::process_incoming_roads()
{
	while (1)
	{
		wait();

		road_stream stream_value = road_input.read();
		if (!stream_value.is_opcode())
		{
		    road_lookup.write(stream_value.get_value());
		}
		command_buffer_write_sig.write(stream_value);
	}

}

// *****************************************************************************
void road_processor::write_FIFO()
{
	while (1)
	{
		wait();

		command_buffer.write(command_buffer_delayed_sig.read());
	}
}

// *****************************************************************************
void road_processor::lookup_superstrips()
{
    while (1)
    {
        wait();

        do
        {
            road_stream actual_command = command_buffer.read();
            if (actual_command.is_opcode())
            {
                for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
                {
                    superstrip_lookup[layer].write(actual_command);
                }
            }
            else
            {
                // wait(found_pattern[0].value_changed_event());

                for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
                {
                    superstrip_lookup[layer].write(found_pattern[layer].read());
                }
            }
        } while (command_buffer.num_available() > 0);
    }

}

// *****************************************************************************
void road_processor::output_result()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            if (hit_lookup_result[layer].event())
            {
                hit_output[layer].write(hit_lookup_result[layer]);
            }
        }
    }

}
