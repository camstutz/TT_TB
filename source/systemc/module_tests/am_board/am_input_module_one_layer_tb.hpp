/*!
 * @file am_input_module_one_layer_tb.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/am_board/am_input_module/am_input_module_one_layer.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class am_input_module_one_layer_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_buffer<bool> start_process_frame_sig;
    sc_buffer<bool> delete_frame_sig;
    sc_buffer<am_input_module_one_layer::frame_t> frame_in_sig;
    sc_signal<bool> frame_available_sig;
    sc_signal<bool> frame_empty_sig;
    sc_signal<bool> frame_processing_sig;
    sc_buffer<track_finder::hit_stream> output_stream;

    // ----- Process Declarations ----------------------------------------------
    void write_frames();
    void print_control();
    void print_stream();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    am_input_module_one_layer dut_am_input_module_one_layer_tb;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_input_module_one_layer_tb(sc_module_name _name);
    SC_HAS_PROCESS(am_input_module_one_layer_tb);
    ~am_input_module_one_layer_tb();

private:
    std::ostringstream log_buffer;
};
