/*!
 * @file fifo_manager_tb.hpp
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

#include <iostream>
#include <sstream>

#include "systemc.h"

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../systems/TT_configuration.hpp"
#include "../modules/backend/fifo_manager/fifo_manager.hpp"
#include "../data_formats/fm_out_data.hpp"
#include "../modules/backend/data_organizer/data_organizer_one_layer.hpp"

/*!
 * @brief
 */
class fifo_manager_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> rst;

    sc_map_square<sc_signal<bool> > dv_inputs;
    sc_map_square<sc_signal<fifo_manager::input_stub_t> > stub_inputs;

    sc_map_square<sc_signal<bool> > neighbour_dv_inputs;
    sc_map_square<sc_signal<fifo_manager::input_stub_t> > neighbour_stub_inputs;
    sc_map_square<sc_signal<bool> > neighbour_dv_outputs;
    sc_map_square<sc_signal<fifo_manager::input_stub_t> > neighbour_stub_outputs;

    sc_map_square<sc_signal<bool> > dv_outputs;
    sc_map_square<sc_signal<fm_out_data> > fifo_outputs;

    // ----- Process Declarations ----------------------------------------------
    void generate_input();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    fifo_manager dut_fifo_manager;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_manager_tb(sc_module_name _name);
    SC_HAS_PROCESS(fifo_manager_tb);
    ~fifo_manager_tb();

private:
    std::ostringstream log_buffer;
};
