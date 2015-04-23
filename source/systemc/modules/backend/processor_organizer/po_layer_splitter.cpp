/*!
 * @file po_layer_splitter.cpp
 * @author Christian Amstutz
 * @date April 22, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "po_layer_splitter.hpp"

// *****************************************************************************

const unsigned int po_layer_splitter::layer_nr = NR_DETECTOR_LAYERS;

// *****************************************************************************

/*!
 * @class po_layer_splitter
 *
 * The module is sensitive to ...
 */

po_layer_splitter::po_layer_splitter(sc_module_name _name) :
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
            unsigned int layer_id = stub.get_stub().get_fe_module() % layer_nr;

            splitted_stubs[layer_id].write(stub);
        }
    }

}
