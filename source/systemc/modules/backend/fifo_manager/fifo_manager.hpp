/*!
 * @file fifo_manager.hpp
 * @author Christian Amstutz
 * @date July 31, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../../systems/TT_configuration.hpp"
#include "../../../data_formats/fm_out_data.hpp"

#include "fifo_manager_controller.hpp"
#include "fifo_manager_datapath.hpp"
#include "../data_organizer/data_organizer_one_layer.hpp"

/*!
 * @brief SystemC module
 */
class fifo_manager : public sc_module
{
public:
    typedef data_organizer_one_layer::do_stub_t input_stub_t;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_map_square<sc_in<bool> > dv_in;
    sc_map_square<sc_in<input_stub_t> > stub_in;

    sc_map_square<sc_in<bool> > neighbour_dv_in;
    sc_map_square<sc_in<input_stub_t> > neighbour_stub_in;
    sc_map_square<sc_out<bool> > neighbour_dv_out;
    sc_map_square<sc_out<input_stub_t> > neighbour_stub_out;

    sc_map_square<sc_out<bool> > dv_out;
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
