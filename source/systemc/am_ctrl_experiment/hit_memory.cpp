/*!
 * @file hit_memory.cpp
 * @author Christian Amstutz
 * @date November 17, 2014
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
        read_event_begin("read_event_begin"),
        read_event_end("read_event_end"),
        write_controller("write_controller")
{

//#ifdef MTI_SYSTEMC
//    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
//    do_stub_out_sig.register_signal_modelsim<do_out_data>();
//    fifo_stub_in.register_signal_modelsim<fm_out_data>();
//#endif

    // ----- Process registration ----------------------------------------------
    SC_THREAD(initialize_event);
        sensitive << read_event_begin;
    SC_THREAD(write_buffer);
        superstrip_inputs.make_sensitive(sensitive);
        substrip_inputs.make_sensitive(sensitive);
    SC_THREAD(search_hits);
        superstrip_search.make_sensitive(sensitive);
    SC_THREAD(write_hits);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    output_buffer.resize(LAYER_NUMBER);

    // ----- Module instance / channel binding ---------------------------------
    write_controller.clk.bind(clk);
    write_controller.hit_inputs.bind(superstrip_inputs);
    write_controller.process_hits.bind(process_hits);
    write_controller.event_begin.bind(read_event_begin);
    write_controller.event_end.bind(read_event_end);

    return;
}

// *****************************************************************************
hit_memory::~hit_memory()
{
    std::cout << endl;
    print_superstrip_table(hit_storage.front()[0]);
    std::cout << endl;
    print_superstrip_table(hit_storage.back()[0]);
    std::cout << endl;

    std::cout << "Printing Output Buffer:" << std::endl;
    while (output_buffer[0].size() > 0)
    {
        std::cout << output_buffer[0].front();
        std::cout << std::endl;
        output_buffer[0].pop();
    }

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
                    std::cout << actual_superstrip << ";" << actual_substrip << std::endl;

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
                superstrip_table_element_t *found_strips = &hit_storage.back()[layer][actual_superstrip];
                if (!found_strips->first)
                {
                    std::list<substrip_t>::iterator strip_it = found_strips->second.begin();
                    for(; strip_it != found_strips->second.end(); ++strip_it)
                    {
                        hit_t composed_hit;
                        composed_hit = actual_superstrip | *strip_it;
                        output_buffer[layer].push(composed_hit);
                    }

                    found_strips->first = true;
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
