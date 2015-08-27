/*!
 * @file po_layer_splitter.cpp
 * @author Christian Amstutz
 * @date August 27, 2015
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
        layer_nr(configuration.layer_nr),
        input_stubs("input_stubs"),
        splitted_stubs(layer_nr, "splitted_stubs")
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
            unsigned int layer_id = stub.get_stub().get_bend() % layer_nr;
            if (!splitted_stubs[layer_id].nb_write(stub))
            {
                std::cerr << sc_time_stamp() << ": FIFO overflow @ "
                          << name() << ".splitted stubs["
                          << layer_id << "]" << std::endl;
            }
        }
    }

}
