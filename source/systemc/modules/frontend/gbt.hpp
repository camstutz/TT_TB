/*!
 * @file gbt.hpp
 * @author Christian Amstutz
 * @date April 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../data_formats/CIC_format/CIC_format.hpp"
#include "../../data_formats/gbt_link_format.hpp"

#include <systemc.h>

#include <vector>
#include <utility>

/*!
 * @brief
 */
template <typename FRAME_TYPE>
class gbt : public sc_module
{
public:
	// ----- Configuration -----------------------------------------------------
	typedef FRAME_TYPE frame_t;
	typedef gbt_link_format<FRAME_TYPE> output_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<frame_t> > cic_in;

    sc_out<output_t> optical_link;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------
    void combine_inputs();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    gbt(sc_module_name _name);
    SC_HAS_PROCESS(gbt);
};
// *****************************************************************************

typedef gbt<CIC_frame_CBC> gbt_cbc;
typedef gbt<CIC_frame_MPA> gbt_mpa;

// *****************************************************************************

// *****************************************************************************
template <typename FRAME_TYPE>
gbt<FRAME_TYPE>::gbt(sc_module_name _name) :
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
template <typename FRAME_TYPE>
void gbt<FRAME_TYPE>::combine_inputs()
{
    while (1)
    {
        wait();

        output_t out_value(cic_in[0].read(), cic_in[1].read() );
        optical_link.write(out_value);
    }

}
