/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date Apr 15, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <systemc.h>
#include <iostream>
#include <string>

#include "hit_generator_tb.hpp"
#include "front_end_chip_tb.hpp"
#include "data_concentrator_tb.hpp"
#include "data_organizer_tb.hpp"
#include "am_board_tb.hpp"
#include "am_system_tb.hpp"


int sc_main(int argc, char *agv[])
{
    // ----- Channel declarations ----------------------------------------------

    // ----- Variable declarations ---------------------------------------------

    // ----- Module instance declarations --------------------------------------

    //hit_generator_tb hit_generator_tb("Hit_Generator_TB");
    //front_end_chip_tb front_end_chip_tb("Front_End_Chip_TB");
    //data_concentrator_tb data_concentrator_tb("Data_Concentrator_TB");
    //data_organizer_tb data_organizer_tb("Data_Organizer_TB");
    am_system_tb am_system_tb("AM_System");
    //am_board_tb am_board_tb("AM_board_TB");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------
    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB_testbench");

//    sc_trace(trace_file, data_concentrator_tb.LHC_clock, "DC_clock");
//    sc_trace(trace_file, data_concentrator_tb.dc_output, "dc_out");
//    sc_trace(trace_file, data_concentrator_tb.dut_data_concentrator.clock_phase, "clk_phase");
//    sc_trace(trace_file, data_concentrator_tb.dut_data_concentrator.stub_buffer_write_sel, "write_sel");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(0,0), "FE_0-0");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(0,1), "FE_0-1");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(1,0), "FE_1-0");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(1,1), "FE_1-1");

//    sc_trace(trace_file, am_board_tb.LHC_clock, "clock");
//    sc_trace(trace_file, am_board_tb.write_en, "");
//    sc_trace(trace_file, am_board_tb.DUT.write_en, "");
//    sc_trace(trace_file, am_board_tb.patterns, "");
//    sc_trace(trace_file, am_board_tb.road_ready, "road_ready");
//    sc_trace(trace_file, am_board_tb.road, "road");
//    sc_trace(trace_file, am_board_tb.DUT.fsm.state, "FSM_state");
//    sc_trace(trace_file, am_board_tb.DUT.detected_roads_buffer_empty, "Buffer_empty");

    sc_trace(trace_file, am_system_tb.LHC_clock, "clock");
    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_not_empty[0], "FIFO_not_empty_0");
    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_read_en[0], "FIFO_read_en_0");
    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].state, "FIFO_FSM_0.state");
    sc_trace(trace_file, am_system_tb.input_fifos[0].stub_out, "FIFO_0.out");

    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.state, "main_FSM.state");

    // ----- Start simulation --------------------------------------------------

    std::cout << std::endl << "Start test bench ..." << std::endl << std::endl;

    //sc_report_handler::set_actions (SC_ID_MORE_THAN_ONE_SIGNAL_DRIVER_, SC_DO_NOTHING);
    sc_start(800, SC_NS);

    sc_close_vcd_trace_file(trace_file);
    std::cout << std::endl << "Test bench ended." << std::endl;

    return (0);
}
