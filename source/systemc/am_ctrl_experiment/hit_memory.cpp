/*!
 * @file hit_memory.cpp
 * @author Christian Amstutz
 * @date November 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_memory.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(hit_memory);
#endif

// *****************************************************************************
hit_memory::hit_memory(const sc_module_name _name) :
        sc_module(_name),
        superstrip_inputs(LAYER_NUMBER, "superstrip_input"),
        substrip_inputs(LAYER_NUMBER, "substrip_input"),
        superstrip_search(LAYER_NUMBER, "superstrip_search"),
        hit_outputs(LAYER_NUMBER, "hit_output"),
        process_hits(LAYER_NUMBER, "process_hits"),
        write_event_begin("read_event_begin"),
        write_event_end("read_event_end"),
        transmit_event_begin("transmit_event_begin"),
        pure_superstrips(LAYER_NUMBER, "pure_superstrips"),
        output_buffer(LAYER_NUMBER, "output_buffer"),
        write_controller("write_controller"),
        lookup_controller("lookup_controller"),
        output_controller("output_controller")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(initialize_event);
        sensitive << write_event_begin;
    SC_THREAD(write_buffer);
        superstrip_inputs.make_sensitive(sensitive);
        substrip_inputs.make_sensitive(sensitive);
    SC_THREAD(search_hits);
        pure_superstrips.make_sensitive(sensitive);
    SC_THREAD(write_hits);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
    write_controller.clk.bind(clk);
    write_controller.hit_inputs.bind(superstrip_inputs);
    write_controller.process_hits.bind(process_hits);
    write_controller.event_begin.bind(write_event_begin);
    write_controller.event_end.bind(write_event_end);

    lookup_controller.clk.bind(clk);
    lookup_controller.superstrip_inputs.bind(superstrip_search);
    lookup_controller.lookup_superstrips.bind(pure_superstrips);
    lookup_controller.event_end.bind(transmit_event_begin);

    output_controller.clk.bind(clk);
    output_controller.start_transmission.bind(transmit_event_begin);
    output_controller.hit_input.bind(output_buffer);
    output_controller.hit_output.bind(hit_outputs);

    return;
}

// *****************************************************************************
void hit_memory::initialize_event()
{
    while(1)
    {
        wait();

        event_set_t empty_table;
        empty_table.resize(LAYER_NUMBER);
        hit_storage.push(empty_table);
    }
}

// *****************************************************************************
void hit_memory::write_buffer()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            if (process_hits[layer].read() &
                (superstrip_inputs[layer].event() |
                substrip_inputs[layer].event()))
            {
                superstrip_t actual_superstrip = superstrip_inputs[layer].read();
                substrip_t actual_substrip = substrip_inputs[layer].read();
                if ((actual_superstrip != IDLE_EVENT) & (actual_superstrip != START_EVENT))
                {
                    superstrip_table_t *superstrip_table = &(hit_storage.back()[layer]);
                    (*superstrip_table)[actual_superstrip].first = false;
                    (*superstrip_table)[actual_superstrip].second.push_back(actual_substrip);
                }
            }
        }
    }

}

// *****************************************************************************
void hit_memory::search_hits()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            superstrip_t actual_superstrip = superstrip_search[layer]->read();
            if ((actual_superstrip != IDLE_EVENT) &
                (actual_superstrip != START_EVENT))
            {
                superstrip_table_t::iterator found_strips = hit_storage.back()[layer].find(actual_superstrip);
                if (found_strips != hit_storage.back()[layer].end())
                {
                    superstrip_table_element_t *table_entry = &found_strips->second;
                    if (!table_entry->first)
                    {
                        std::list<substrip_t>::iterator strip_it = table_entry->second.begin();
                        for(; strip_it != table_entry->second.end(); ++strip_it)
                        {
                            hit_t composed_hit;
                            composed_hit = (actual_superstrip << SS_BIT_WIDTH) | *strip_it;
                            output_buffer[layer].write(composed_hit);
                        }

                        table_entry->first = true;
                    }
                }
            }
        }
    }

}

// *****************************************************************************
void hit_memory::write_hits()
{
    while (1)
    {
        wait();

//        output_data_ready_no_delay.write(false);
//
//        if (write_roads_sig)
//        {
//            if (!output_roads_buffer_empty)
//            {
//                road_addr_t road = detected_roads_buffer.read();
//                output_data_ready_no_delay.write(true);
//                output_road_no_delay.write(road);
//            }
//        }
    }
}

// *****************************************************************************
void hit_memory::print_superstrip_table(superstrip_table_t table)
{
    std::cout << "Super Strip Table:" << std::endl;
    superstrip_table_t::iterator table_it = table.begin();
    for (; table_it != table.end(); ++table_it)
    {
        std::cout << "SS=" << table_it->first << ": ";
        if (table_it->second.first)
        {
            std::cout << "X";
        }
        else
        {
            std::cout << "O";
        }
        std::cout << " - ";

        std::list<substrip_t> substrip_list = table_it->second.second;
        std::list<substrip_t>::iterator substrip_it = substrip_list.begin();
        for (; substrip_it != substrip_list.end(); ++substrip_it)
        {
            std::cout << *substrip_it << ", ";
        }

        std::cout << std::endl;
    }
}
