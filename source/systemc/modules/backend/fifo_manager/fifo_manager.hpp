/*!
 * @file fifo_manager.hpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
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
    typedef fifo_manager_datapath::input_stub_t input_stub_t;
    typedef fifo_manager_datapath::output_t output_t;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Data valid inputs for the stub inputs of this trigger tower. The
     *  dimensions of sc_map are (layer, stub number). */
    sc_map_square<sc_in<bool> > dv_in;
    /** The stub inputs of the trigger tower. The dimensions of sc_map are
     *  (layer, stub number). */
    sc_map_square<sc_in<input_stub_t> > stub_in;

    /** Inputs for the data valid signals of the neighboring trigger towers. The
     *  dimensions of sc_map are (tower, layer). */
    sc_map_square<sc_in<bool> > neighbour_dv_in;
    /** Inputs for the stubs from the neighboring trigger towers. The dimensions
     *  of sc_map are (tower, layer). */
    sc_map_square<sc_in<input_stub_t> > neighbour_stub_in;
    /** Outputs for the data valid signals of the neighboring trigger towers.
     *  The dimensions of sc_map are (tower, layer). */
    sc_map_square<sc_out<bool> > neighbour_dv_out;
    /** Outputs for the stubs from the neighboring trigger towers. The
     *  dimensions of sc_map are (tower, layer). */
    sc_map_square<sc_out<input_stub_t> > neighbour_stub_out;

    /** Data valid output to signal the availability of data to the FIFO. The
     *  the dimensions within sc_map are (AM lane, layer). */
    sc_map_square<sc_out<bool> > dv_out;
    /** Data output to the FIFOs. The dimensions within sc_map are
     *  (AM lane, layer). */
    sc_map_square<sc_out<output_t> > fifo_out;

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
