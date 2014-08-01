/*!
 * @file fifo_manager_datapath.hpp
 * @author Christian Amstutz
 * @date Aug 1, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <queue>
#include <vector>

#include <systemc.h>
#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../../libraries/systemc_helpers/nbits.hpp"

#include "../../../systems/TT_configuration.hpp"
#include "../../../data_formats/fm_out_data.hpp"
#include "../data_organizer/data_organizer_one_layer.hpp"

/*!
 * @brief
 */
class fifo_manager_datapath : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_map_linear<sc_in<bool> > buffer_write_en;
    sc_map_linear<sc_in<bool> > buffer_read_en;
    sc_in<unsigned int> time_stamp;

    sc_map_linear<sc_in<bool> > dv_in;
    sc_map_linear<sc_in<data_organizer_one_layer::do_stub_t> > stub_in;

    sc_map_linear<sc_in<bool> > neighbour_dv_in;
    sc_map_linear<sc_in<data_organizer_one_layer::do_stub_t> > neighbour_stub_in;
    sc_map_linear<sc_in<bool> > neighbour_dv_out;
    sc_map_linear<sc_in<data_organizer_one_layer::do_stub_t> > neighbour_stub_out;

    sc_map_linear<sc_out<bool> > dv_out;
    sc_map_linear<sc_out<fm_out_data> > fifo_out;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

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

    std::vector<std::queue<fm_out_data> > stub_buffer;
};
