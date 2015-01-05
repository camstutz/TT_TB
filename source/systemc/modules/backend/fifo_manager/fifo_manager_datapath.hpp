/*!
 * @file fifo_manager_datapath.hpp
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

#include <queue>
#include <vector>

#include <systemc.h>
#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../../libraries/systemc_helpers/nbits.hpp"

#include "../../../systems/TT_configuration.hpp"
#include "../../../data_formats/fm_out_data.hpp"

/*!
 * @brief
 */
class fifo_manager_datapath : public sc_module
{
public:
    typedef do_stub_t input_stub_t;
    typedef fm_out_data output_t;
    typedef std::vector<unsigned int> neighbour_vector;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_map_linear<sc_in<bool> > buffer_write_en;
    sc_map_linear<sc_in<bool> > buffer_read_en;
    sc_in<unsigned int> time_stamp;

    sc_map_linear<sc_in<bool> > dv_in;
    sc_map_linear<sc_in<input_stub_t> > stub_in;

    sc_map_linear<sc_in<bool> > neighbour_dv_in;
    sc_map_linear<sc_in<input_stub_t> > neighbour_stub_in;
    sc_map_linear<sc_out<bool> > neighbour_dv_out;
    sc_map_linear<sc_out<input_stub_t> > neighbour_stub_out;

    sc_map_linear<sc_out<bool> > dv_out;
    sc_map_linear<sc_out<output_t> > fifo_out;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void read_stubs();
    void write_fifos();
    void write_neighbours();

// ----- Other Method Declarations ---------------------------------------------
    neighbour_vector neighbour_selector(input_stub_t stub) const;

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_manager_datapath(sc_module_name _name);
    SC_HAS_PROCESS(fifo_manager_datapath);

private:

    std::vector<std::queue<fm_out_data> > stub_buffer;
    std::vector<std::queue<input_stub_t> > neighbour_buffer;
};
