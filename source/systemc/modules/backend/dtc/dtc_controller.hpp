/*!
 * @file dtc_controller.hpp
 * @author Christian Amstutz
 * @date April 13, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_controller_config.hpp"

#include <systemc.h>

/*!
 * @brief
 */
class dtc_controller : public sc_module
{
public:
    const unsigned int fe_collect_cycles;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_out<unsigned int> bunch_crossing;
    sc_out<unsigned int> write_buffer;
    sc_out<unsigned int> read_buffer;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void update_signals();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    dtc_controller(sc_module_name _name, dtc_controller_config configuration);
    SC_HAS_PROCESS(dtc_controller);

private:
    unsigned int bx_counter;
};
