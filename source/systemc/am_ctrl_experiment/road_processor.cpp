/*!
 * @file road_processor.cpp
 * @author Christian Amstutz
 * @date November 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
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
        filtered_hits(LAYER_NUMBER, "filtered_hits")
{
	// ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_roads);
        sensitive << road_input;
    SC_THREAD(lookup_superstrips);
        sensitive << command_buffer.data_written_event();


    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
    //hit_lookup_result.bind(filtered_hits);
    //hit_output.bind(hit_lookup_result);

    return;
}

// *****************************************************************************
void road_processor::process_incoming_roads()
{
	while(1)
	{
		wait();

		road_t detected_road = road_input.read();

		if ((detected_road == IDLE_EVENT) || (detected_road == START_EVENT))
		{
		    command_buffer.write(detected_road);
		}
		else
		{
		    road_lookup.write(detected_road);
		    command_buffer.write(VALUE_EVENT);
		}
	}

}

// *****************************************************************************
void road_processor::lookup_superstrips()
{
    while(1)
    {
        wait();

        do
        {
            unsigned int actual_command = command_buffer.read();
            switch (actual_command)
            {
            case IDLE_EVENT:
            case START_EVENT:
                for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
                {
                    superstrip_lookup[layer].write(actual_command);
                }
                break;

            case VALUE_EVENT:
                wait(found_pattern[0].value_changed_event());

                for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
                {
                    superstrip_lookup[layer].write(found_pattern[layer].read());
                }
                break;

            default:
                for (unsigned int layer; layer < LAYER_NUMBER; ++layer)
                {
                    superstrip_lookup[layer].write(IDLE_EVENT);
                }
                break;
            }
        } while (command_buffer.num_available() > 0);
    }

}
