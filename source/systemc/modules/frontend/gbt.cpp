/*!
 * @file gbt.cpp
 * @author Christian Amstutz
 * @date April 10, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "gbt.hpp"

// *****************************************************************************
gbt::gbt(sc_module_name _name) :
    sc_module(_name),
    clk("clk"),
    cic_in(2, "cic_in"),
    optical_link("optical_link")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(combine_inputs);
        sensitive << clk.pos();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void gbt::combine_inputs()
{
    while (1)
    {
        wait();

        output_t out_value(cic_in[0].read(), cic_in[1].read() );
        optical_link.write(out_value);
    }

}
