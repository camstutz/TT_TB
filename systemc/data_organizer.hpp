/*!
 * @file data_organizer.hpp
 * @author Christian Amstutz
 * @date Apr 17, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <sstream>
#include <vector>

#include <systemc.h>
#include "../lib/systemc_helpers/sc_map/sc_map.hpp"
//#include "../lib/systemc_helpers/nbits.hpp"

#include "TT_configuration.hpp"
#include "data_representations/do_out_data.hpp"
#include "data_organizer_one_layer.hpp"

/*!
 * @brief SystemC module to split up the serial data from the detector into the
 * different stubs.
 *
 * This module takes the serial packets from the detector itself (in the real
 * system probably by the Glib transmission system) and rearranges the data, so
 * the data at the output is again sorted by stubs. The stubs are also reordered
 * according to their time stamp, thereby the whole system has a constant
 * latency.
 */
class data_organizer : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    /** Linear sc_map for the stream inputs. There exist a seperate input for
      * ever layer of the detector */
    sc_map_linear<sc_in<sc_bv<DC_OUTPUT_WIDTH> > >stream_in;

    /** Linear sc_map for the re-arranged, re-timed stubs. */
    sc_map_linear<sc_out<do_out_data> > stub_out;

// ----- Local Channel Declarations --------------------------------------------
    /** Control signal showing the actual time step of within the time window */
    sc_signal<sc_uint<3> > clock_phase;

    /** Control signal that switches between the two re-order tables */
    sc_signal<unsigned int> stub_table_sel;

    sc_signal<unsigned int> phi_sig;
    sc_signal<unsigned int> z_sig;


// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void controller();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    sc_map_linear<data_organizer_one_layer> do_one_layer_map;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer(sc_module_name _name, unsigned int phi, unsigned int z);
    SC_HAS_PROCESS(data_organizer);

private:
    const unsigned int phi;
    const unsigned int z;
};
