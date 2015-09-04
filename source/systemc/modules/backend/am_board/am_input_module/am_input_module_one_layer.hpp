/*!
 * @file am_input_module_one_layer.hpp
 * @author Christian Amstutz
 * @date April 22, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../track_finder/track_finder.hpp"
#include "../../../../data_formats/prbf/PRBF.hpp"
//#include "../../../../systems/TT_configuration.hpp"
#include "../../../../systems/tt_tb_logger.hpp"

#include <systemc.h>

#include <queue>

/*!
 * @brief SystemC
 */
class am_input_module_one_layer : public sc_module
{
public:
    typedef PRBF_2 frame_t;
    typedef track_finder::hit_stream::value_t hit_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> start_process_frame;
    sc_in<bool> delete_frame;
    sc_in<frame_t> frame_input;
    sc_out<bool> frame_available;
    sc_out<bool> frame_empty;
    sc_out<bool> frame_processing;
    sc_out<track_finder::hit_stream> stub_stream_output;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------
    void read_frames();
    void update_control_output();
    void process_one_frame();
    void create_stream();

    // ----- Other Method Declarations -----------------------------------------
    hit_t get_AM_hit_address(frame_t::stub_t stub);

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_input_module_one_layer(const sc_module_name _name);
    SC_HAS_PROCESS(am_input_module_one_layer);

    frame_t processed_frame;

private:
    typedef std::queue<frame_t> frame_buffer_t;

    frame_buffer_t input_frame_buffer;
};
