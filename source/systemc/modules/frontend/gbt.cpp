/*!
 * @file gbt.cpp
 * @author Christian Amstutz
 * @date April 27, 2015
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
    cic_in(2, "cic_in"),
    optical_link("optical_link")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(combine_inputs);
        cic_in.make_sensitive(sensitive);

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

        if ((cic_in[0].read().stub_count() > 0) | (cic_in[1].read().stub_count() > 0))
        {
            SYSTEMC_LOG << "Frames @ bx=" << cic_in[0].read().get_header().get_bunch_crossing()
                    << " with "
                    << cic_in[0].read().stub_count() << "|"
                    << cic_in[1].read().stub_count()
                    << " stubs transmitted.";
        }
    }

}
