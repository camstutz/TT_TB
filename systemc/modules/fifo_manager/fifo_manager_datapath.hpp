/*!
 * @file fifo_manager_datapath.hpp
 * @author Christian Amstutz
 * @date Apr 28, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <queue>
#include <array>

#include <systemc.h>
#include "../../../lib/systemc_helpers/sc_map/sc_map.hpp"
#include "../../../lib/systemc_helpers/nbits.hpp"

#include "../../TT_configuration.hpp"
#include "../../data_representations/do_out_data.hpp"
#include "../../data_representations/fm_out_data.hpp"

/*!
 * @brief
 */
class fifo_manager_datapath : public sc_module
{
public:
    //typedef typename std::array<std::vector<sc_bv<16> >, NR_DC_WINDOW_CYCLES > stub_table_type;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_map_linear<sc_in<bool>> buffer_write_en;
    sc_map_linear<sc_in<bool>> buffer_read_en;
    sc_in<unsigned int> time_stamp;

    sc_map_linear<sc_in<do_out_data>> stub_in;
    sc_map_linear<sc_out<fm_out_data>> fifo_out;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------
    //std::array<stub_table_type, 2> stub_table;

// ----- Process Declarations --------------------------------------------------
    void read_stubs();
    void write_fifos();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_manager_datapath(sc_module_name _name);
    SC_HAS_PROCESS(fifo_manager_datapath);

private:

    std::array<std::queue<fm_out_data>, NR_AM_BOARDS> stub_buffer;
};
