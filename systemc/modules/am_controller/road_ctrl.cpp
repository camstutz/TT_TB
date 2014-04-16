/*!
 * @file road_ctrl.cpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "road_ctrl.hpp"

// *****************************************************************************

/*!
 * @class road_ctrl
 *
 * The module is sensitive to ...
 */

road_ctrl::road_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        init("init"),
        data_ready_road("data_ready_road"),
        road_in("road_in"),
        finish_road("finish_road"),
        write_en_road("write_en_road"),
        road_out("road_out"),
        write_en_sig("write_en_sig"),
        road_sig("road_sig")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(transfer_roads);
        sensitive << clk.pos();
    SC_THREAD(generate_finish_road);
        sensitive << data_ready_road << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void road_ctrl::transfer_roads()
{
    while (1)
    {
        wait();

        write_en_road.write(data_ready_road.read());
        road_out.write(road_in.read());
    }
}

// *****************************************************************************
void road_ctrl::generate_finish_road()
{
    while (1)
    {
        finish_road.write(false);

        if (data_ready_road.negedge())
        {
            finish_road.write(true);
        }

        wait();
    }
}
