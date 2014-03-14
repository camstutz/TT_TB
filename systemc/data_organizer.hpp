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
 * @brief
 */

class data_organizer : public sc_module
{
public:
    typedef typename std::array<std::vector<sc_bv<16> >, NR_DC_WINDOW_CYCLES > stub_table_type;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_map_linear<sc_in<sc_bv<DC_OUTPUT_WIDTH> > >stream_in;
    sc_map_linear<sc_out<do_out_data> > stub_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<sc_uint<3> > clock_phase;
    sc_signal<unsigned int> stub_table_sel;
    //sc_fifo<sc_bv<DC_OUTPUT_WIDTH> > input_buffer;

    // ----- Storage Declarations ----------------------------------------------
    std::array<stub_table_type, 2> stub_table;


    // ----- Process Declarations ----------------------------------------------
    void controller();
    void read_input();
    void sort_stubs();
    void write_stubs();

    void print_table();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer(sc_module_name _name, unsigned int phi, unsigned int z);
    SC_HAS_PROCESS(data_organizer);

private:
    const unsigned int phi;
    const unsigned int z;
};
