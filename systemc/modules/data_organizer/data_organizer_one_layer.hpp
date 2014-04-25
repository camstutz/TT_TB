/*!
 * @file data_organizer_one_layer.hpp
 * @author Christian Amstutz
 * @date Apr 20, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <sstream>
#include <array>
#include <vector>

#include <systemc.h>
#include "../../../lib/systemc_helpers/sc_map/sc_map.hpp"
#include "../../../lib/systemc_helpers/nbits.hpp"

#include "../../TT_configuration.hpp"
#include "../../data_representations/do_out_data.hpp"

/*!
 * @brief
 */
class data_organizer_one_layer : public sc_module
{
public:
    typedef typename std::array<std::vector<sc_bv<16> >, NR_DC_WINDOW_CYCLES >
            stub_table_type;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_in<unsigned int> time_stamp;

    /** Control signal showing the actual time step of within the time window */
    sc_in<sc_uint<3> > clock_phase;

    /** Control signal that switches between the two re-order tables */
    sc_in<unsigned int> stub_table_sel;

    sc_in<sc_bv<DC_OUTPUT_WIDTH>>stream_in;

    /** Linear sc_map for the re-arranged, re-timed stubs. */
    sc_map_linear<sc_out<do_out_data>> stub_out;

    // todo: put these values to constructor
    sc_in<unsigned int> phi;
    sc_in<unsigned int> z;

// ----- Local Channel Declarations --------------------------------------------

    /** Intermediate buffer for the incoming data */
    sc_buffer<sc_bv<DC_OUTPUT_WIDTH-2> > input_buffer;

// ----- Local Storage Declarations --------------------------------------------
    /** Two tables for the re-arranged stubs. Each table can contain a defined
     * number of stubs for each time step of the time window of the data
     * transmission. */
    std::array<stub_table_type, 2> stub_table;


// ----- Process Declarations --------------------------------------------------
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
    data_organizer_one_layer(sc_module_name _name);
    SC_HAS_PROCESS(data_organizer_one_layer);

private:

};
