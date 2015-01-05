/*!
 * @file data_organizer.hpp
 * @author Christian Amstutz
 * @date Janaury 5, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <sstream>
#include <vector>

#include <systemc.h>
#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../../systems/TT_configuration.hpp"

#include "data_organizer_one_layer.hpp"
#include "data_organizer_one_layer_mpa.hpp"
#include "data_organizer_one_layer_cbc.hpp"

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
    typedef data_organizer_one_layer::do_in_t do_in_t;
    typedef data_organizer_one_layer::do_out_t do_out_t;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Linear sc_map for the stream inputs. There exist a separate input for
      * every layer of the detector */
    sc_map_linear<sc_in<do_in_t> >stream_in;

    /** Square sc_map for the re-arranged, re-timed stubs and the according data
     * valid lines.
     */
    sc_map_square<sc_out<bool> > dv;
    sc_map_square<sc_out<do_out_t> > stub_out;

// ----- Local Channel Declarations --------------------------------------------
    /** Control signal showing the actual time step of within the time window */
    sc_signal<sc_uint<3> > clock_phase;

    /** Control signal that switches between the two re-order tables */
    sc_signal<unsigned int> stub_table_sel;

    sc_signal<unsigned int> time_stamp;
    sc_signal<unsigned int> phi_sig;
    sc_signal<unsigned int> z_sig;

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void controller();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    sc_map_linear<data_organizer_one_layer_mpa> do_one_layer_map_mpa;
    sc_map_linear<data_organizer_one_layer_cbc> do_one_layer_map_cbc;

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
