/*!
 * @file data_organizer.hpp
 * @author Christian Amstutz
 * @date Mar 14, 2014
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

#include "TT_configuration.hpp"
#include "do_out_data.hpp"

/*!
 * @brief SystemC module to split up the serial data from the detector into the
 * different stubs.
 *
 * This module takes the serial packets from the detector itself (in the real
 * system probably by the Glib transmission system) and rearranges the data, so
 * the data at the output is again sorted by stubs. The stubs are also reordered
 * according to their time stamp, thereby the whole system has a constant
 * latency.\n
 * So far it works only for layer 1.
 */
class data_organizer : public sc_module
{
public:
    typedef typename std::array<std::vector<sc_bv<16> >, NR_DC_WINDOW_CYCLES >
            stub_table_type;

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
    /** todo: change the value to generic */
    sc_signal<sc_uint<3> > clock_phase;

    /** Control signal that switches between the two re-order tables */
    sc_signal<unsigned int> stub_table_sel;

    /** Intermediate buffer for the incoming data */
    sc_buffer<sc_bv<DC_OUTPUT_WIDTH-2> > input_buffer;

// ----- Local Storage Declarations --------------------------------------------
    /** Two tables for the re-arranged stubs. Each table can contain a defined
     * number of stubs for each time step of the time window of the data
     * transmission. */
    std::array<stub_table_type, 2> stub_table;


// ----- Process Declarations --------------------------------------------------
    void controller();
    void read_input();
    void sort_stubs();
    void write_stubs();

    void print_table();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

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
