/*!
 * @file road_ctrl.cpp
 * @author Christian Amstutz
 * @date Apr 21, 2014
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
        event_tag("event_tag"),
        road_in("road_in"),
        finish_road("finish_road"),
        write_en_road("write_en_road"),
        road_out("road_out"),
        write_en_sig("write_en_sig"),
        road_sig("road_sig"),
    	data_ready_last("data_ready_last")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(transfer_roads);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void road_ctrl::transfer_roads()
{
	data_ready_last.write(false);

    while (1)
    {
        wait();

        finish_road.write(false);

        write_en_road.write(data_ready_road.read());
        road_out.write(road_in.read());

        if ((data_ready_last.read() == true) & (data_ready_road.read() == false))
        {
        	finish_road.write(true);
            write_en_road.write(true);
            road_out.write(event_tag.read());
        }

        data_ready_last.write(data_ready_road.read());
    }
}
