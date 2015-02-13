/*!
 * @file fifo_ctrl.cpp
 * @author Christian Amstutz
 * @date February 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "fifo_ctrl.hpp"

// *****************************************************************************

/*!
 * @class hit_ctrl_single_line
 *
 * The module is sensitive to ...
 */

fifo_ctrl::fifo_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        new_hit("new_hit"),
        wr_hit_lamb("wr_hit_lamb"),
        init_event("init_ev"),
        stub_input("stub_input"),
        hee_reg("hee_reg"),
        write_en("write_en"),
        stub_output("stub_output"),
        stub_tag("stub_tag"),
        FSM("FSM")
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
    FSM.clk.bind(clk);
//  FSM.fifo_write_en.bind();
//  FSM.fifo_not_empty.bind();
//  FSM.is_timestamp.bind();
//  FSM.event_active.bind();
//  FSM.fifo_read_en.bind();

    return;
}

// *****************************************************************************
void fifo_ctrl::read_input_stub()
{
    while (1)
    {
        wait();

        if (new_hit.read() == true)
        {
            fm_out_data stub = stub_input.read();
            stub_read.write(stub);
        }

        if (init_event.read() == 7)
        {
            stub_read.write(fm_out_data(fm_out_data::fm_stub_t()));
        }
    }

}

// *****************************************************************************
void fifo_ctrl::write_AM_stub()
{
    while (1)
    {
        wait();

        if (wr_hit_lamb.read() == true)
        {
            fm_out_data::fm_stub_t strip_addr;
            sc_bv<AM_BOARD_PATTERN_WIDTH> pattern;
            strip_addr = stub_read.read().get_data_stub();

            // Super strip generation
            pattern = strip_addr.get_bitvector()(AM_BOARD_PATTERN_WIDTH-1,0);
            pattern = pattern & 0x00FF;

            stub_output.write(pattern);
        }
        write_en.write(wr_hit_lamb.read());
    }

}

// *****************************************************************************
void fifo_ctrl::update_tag()
{
	while (1)
	{
		wait ();

		if (hee_reg.read() == true)
		{
			stub_tag.write(stub_read.read().is_timestamp());
		}
	}
}
