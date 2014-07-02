/*!
 * @file frontend_chip_mpa.hpp
 * @author Christian Amstutz
 * @date July 2, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"
#include "../../data_formats/stub_bxsbp.hpp"

/*!
 * @brief
 */
class frontend_chip_mpa : public sc_module
{
public:

    typedef stub_bxsbp<FE_MPA_STUB_BX_BITS,
                       FE_MPA_STUB_STRIP_BITS,
                       FE_MPA_STUB_BEND_BITS,
                       FE_MPA_STUB_PIXEL_BITS,
                       FE_MPA_STUB_BX_BITS+FE_MPA_STUB_STRIP_BITS
                       +FE_MPA_STUB_BEND_BITS+FE_MPA_STUB_PIXEL_BITS> fe_mpa_stub_t;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> en;
    sc_fifo_in<fe_mpa_stub_t> stub_input;
    sc_map_linear<sc_out<bool> > data_valids;
    sc_map_linear<sc_out<fe_mpa_stub_t> > stub_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<fe_mpa_stub_t> selected_stubs;

// ----- Process Declarations --------------------------------------------------
    void prioritize_hits();
    void write_hits();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    frontend_chip_mpa(const sc_module_name _name);
    SC_HAS_PROCESS(frontend_chip_mpa);
};
