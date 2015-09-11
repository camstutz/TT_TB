/*!
 * @file po_layer_splitter.cpp
 * @author Christian Amstutz
 * @date September 11, 2015
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
        splitted_stubs(configuration.layer_nr, "splitted_stubs")
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
            local_module_address local_address = local_module_address(configuration.trigger_tower_id, local_prb, local_dtc, local_mod);

            po_layer_splitter_config::layer_lookup_table_t::const_iterator layer_it = configuration.layer_lookup_table.find(local_address);
            if (layer_it != configuration.layer_lookup_table.end())
            {
                unsigned int layer_id = layer_it->second;
                if (!splitted_stubs[layer_id].nb_write(stub))
                {
                    std::cerr << sc_time_stamp() << ": FIFO overflow @ "
                              << name() << ".splitted stubs["
                              << layer_id << "]" << std::endl;
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
