/*!
 * @file hit_ctrl_single_line.cpp
 * @author Christian Amstutz
 * @date Apr 20, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_ctrl_single_line.hpp"

// *****************************************************************************

/*!
 * @class hit_ctrl_single_line
 *
 * The module is sensitive to ...
 */

hit_ctrl_single_line::hit_ctrl_single_line(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        new_hit("new_hit"),
        wr_hit_lamb("wr_hit_lamb"),
        init_event("init_ev"),
        stub_input("stub_input"),
        hee_reg("hee_reg"),
        write_en("write_en"),
        stub_output("stub_output"),
        stub_tag("stub_tag")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input_stub);
        sensitive << clk.pos() << init_event;
    SC_THREAD(write_AM_stub);
        sensitive << clk.pos();
    SC_THREAD(update_hee_reg)
        sensitive << stub_read << stub_input;
    SC_THREAD(update_tag);
    	sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void hit_ctrl_single_line::read_input_stub()
{
    while (1)
    {
        wait();

        if (new_hit.read() == true)
        {
            auto stub = stub_input.read();
            stub_read.write(stub);
        }

        if (init_event.read() == 7)
        {
            stub_read.write(fm_out_data(fm_out_data::fm_stub_t()));
        }
    }

}

// *****************************************************************************
void hit_ctrl_single_line::write_AM_stub()
{
    while (1)
    {
        wait();

        if (wr_hit_lamb.read() == true)
        {
            stub_output.write(stub_read.read().get_data()(15,0));
        }
        write_en.write(wr_hit_lamb.read());
    }

}

// *****************************************************************************
void hit_ctrl_single_line::update_hee_reg()
{
    while (1)
    {
        hee_reg_before.write(stub_input.read().get_time_stamp_flag());
        hee_reg.write(stub_read.read().get_time_stamp_flag());

        wait();
    }


}

// *****************************************************************************
void hit_ctrl_single_line::update_tag()
{
	while (1)
	{
		wait ();

		if (hee_reg.read() == true)
		{
			stub_tag.write(stub_read.read().get_data_time_stamp());
		}
	}
}
