/*!
 * @file fifo_manager.hpp
 * @author Christian Amstutz
 * @date May 19, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "../../TT_configuration.hpp"
#include "../../data_representations/do_out_data.hpp"
#include "../../data_representations/fm_out_data.hpp"

#include "fifo_manager_controller.hpp"
#include "fifo_manager_datapath.hpp"

/*!
 * @brief SystemC module
 */
class fifo_manager : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_map_square<sc_in<do_out_data> > stub_in;

    sc_map_square<sc_out<fm_out_data> > fifo_out;

// ----- Local Channel Declarations --------------------------------------------
    sc_map_linear<sc_signal<bool> > buf_write_en_sig;
    sc_map_linear<sc_signal<bool> > buf_read_en_sig;
    sc_signal<unsigned int> time_stamp_sig;

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    fifo_manager_controller controller;
    sc_map_linear<fifo_manager_datapath> datapaths;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_manager(sc_module_name _name);
    SC_HAS_PROCESS(fifo_manager);

private:

};
