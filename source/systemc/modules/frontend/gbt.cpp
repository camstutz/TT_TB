/*!
 * @file gbt.cpp
 * @author Christian Amstutz
 * @date May 5, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "gbt.hpp"

// *****************************************************************************
gbt::gbt(sc_module_name _name, gbt_config configuration) :
    sc_module(_name),
    input_link_count(configuration.input_link_count),
    cic_in(input_link_count, "cic_in"),
    optical_link("optical_link")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(combine_inputs);
        sensitive << cic_in;

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

        // TODO: adapt to more than 2 inputs

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
