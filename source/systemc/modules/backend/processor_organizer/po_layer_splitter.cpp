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
        splitted_stubs(configuration.get_layer_nr(), "splitted_stubs")
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
            prbf_module_address local_address = prbf_module_address(configuration.get_trigger_tower_id(), local_prb, local_dtc, local_mod);

            std::pair<bool, unsigned int> layer_result = configuration.get_layer(local_address);
            if (layer_result.first)
            {
                unsigned int layer_id = layer_result.second;
                unsigned int output_id = configuration.get_layer_pos(layer_id);
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
