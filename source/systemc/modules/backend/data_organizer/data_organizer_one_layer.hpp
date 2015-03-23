/*!
 * @file data_organizer_one_layer.hpp
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

#define DC_output_delay 5

#include <sstream>
#include <vector>

#include <systemc.h>
#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"

#include "../../../systems/TT_configuration.hpp"

/*!
 * @brief
 */
class data_organizer_one_layer : public sc_module
{
public:
    typedef do_stub_t do_out_t;
    typedef dc_out_t do_in_t;

    typedef typename std::vector<std::vector<do_stub_t > > stub_table_type;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_in<unsigned int> time_stamp;

    /** Control signal showing the actual time step of within the time window */
    sc_in<sc_uint<3> > clock_phase;

    /** Control signal that switches between the two re-order tables */
    sc_in<unsigned int> stub_table_sel;

    sc_in<do_in_t> stream_in;

    /** Linear sc_map for the re-arranged, re-timed stubs. */
    sc_map_linear<sc_out<bool> > dv;
    sc_map_linear<sc_out<do_out_t> > stub_out;

    // todo: put these values to constructor
    sc_in<unsigned int> phi;
    sc_in<unsigned int> z;

// ----- Local Channel Declarations --------------------------------------------
    /** Intermediate buffer for the incoming data */
    sc_buffer<dc_out_t::payload_t> input_buffer;

    sc_map_linear<sc_signal<bool> > dv_sig;
    sc_map_linear<sc_signal<do_out_t> > stub_out_sig;

// ----- Local Storage Declarations --------------------------------------------
    /** Two tables for the re-arranged stubs. Each table can contain a defined
     * number of stubs for each time step of the time window of the data
     * transmission. */
    std::vector<stub_table_type> stub_table;

    sc_bv<2*dc_out_t::total_width> concat_buffer;
    unsigned int cc_buf_write_ptr;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void sort_stubs();
    void write_stubs();

    void print_table();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    sc_map_linear<sc_delay_signal<bool, DC_output_delay> > delay_dv;
    sc_map_linear<sc_delay_signal<do_out_t, DC_output_delay> > delay_stub_out;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer_one_layer(sc_module_name _name);
    SC_HAS_PROCESS(data_organizer_one_layer);

protected:

    virtual void process_input_buffer() =0;
};
