/*!
 * @file fifo_manager.cpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_manager.hpp"

// *****************************************************************************

/*!
 * @class data_organizer
 *
 * The module is sensitive to clk.pos and the change of the input_buffer.
 */

fifo_manager::fifo_manager(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst")
{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
//    unsigned int layer = 0;
//    for (auto& one_do : do_one_layer_map)
//    {
//        ++layer;
//    }

    return;
}
