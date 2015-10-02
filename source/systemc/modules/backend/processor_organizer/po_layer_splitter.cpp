/*!
 * @file po_layer_splitter.cpp
 * @author Christian Amstutz
 * @date October 2, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "po_layer_splitter.hpp"

// *****************************************************************************

/*!
 * @class po_layer_splitter
 *
 * The module is sensitive to ...
 */

po_layer_splitter::po_layer_splitter(sc_module_name _name,
        po_layer_splitter_config configuration) :
        configuration(configuration),
        input_stubs("input_stubs"),
        splitted_stubs(configuration.layers.size(), "splitted_stubs")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(split_stubs);
        sensitive << input_stubs.data_written();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void po_layer_splitter::split_stubs()
{
    while (1)
    {
        wait();

        while (input_stubs.num_available() > 0)
        {
            element_t stub = input_stubs.read();

            unsigned int local_prb = stub.get_stub().get_prb();
            unsigned int local_dtc = stub.get_stub().get_dtc();
            unsigned int local_mod = stub.get_stub().get_fe_module();
            prbf_module_address local_address = prbf_module_address(configuration.trigger_tower_id, local_prb, local_dtc, local_mod);

            po_layer_splitter_config::layer_lookup_table_t::const_iterator layer_it = configuration.layer_lookup_table.find(local_address);
            if (layer_it != configuration.layer_lookup_table.end())
            {
                unsigned int layer_id = layer_it->second;
                unsigned int output_id = std::distance(configuration.layers.begin(), configuration.layers.find(layer_id));
                if (!splitted_stubs[output_id].nb_write(stub))
                {
                    std::cerr << sc_time_stamp() << ": FIFO overflow @ "
                              << name() << ".splitted stubs["
                              << output_id << "]" << std::endl;
                }
            }
            else
            {
                std::cerr << sc_time_stamp() << ": Layer for module "
                          << local_address << " could not be retrieved."
                          << std::endl;
            }
        }
    }

}

// *****************************************************************************
void po_layer_splitter::print_layer_table()
{
    std::cout << "Layer Translation table of " << name()
              << " sized " << configuration.layer_lookup_table.size() << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    for (po_layer_splitter_config::layer_lookup_table_t::const_iterator layer_table_line = configuration.layer_lookup_table.begin();
         layer_table_line != configuration.layer_lookup_table.end();
         ++layer_table_line)
    {
        std::cout << layer_table_line->first
                  << " --> "
                  << layer_table_line->second
                  << std::endl;
    }

    return;
}
