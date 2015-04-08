/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include <systemc.h>
#include <iostream>
#include <string>

//#include "hit_file_test.hpp"
//#include "hit_generator_tb.hpp"
//#include "frontend_chip_cbc_tb.hpp"
//#include "frontend_chip_mpa_tb.hpp"
#include "data_concentrator_cbc_tb.hpp"
//#include "data_concentrator_mpa_tb.hpp"
//#include "data_organizer_tb.hpp"
//#include "fifo_manager_tb.hpp"
//#include "fifo_manager_datapath_tb.hpp"
//#include "am_board_tb.hpp"
//#include "am_system_tb.hpp"
//#include "trigger_tower_tb.hpp"
//#include "prbf_tb.hpp"
//#include "cic_format_tb.hpp"

int sc_main(int argc, char *agv[])
{
    // ----- Set up tracing ----------------------------------------------------
    sc_trace_file *trace_file;
    trace_file = sc_create_vcd_trace_file("TT_TB_testbench");

    //hit_file_test();

    // ----- Channel declarations ----------------------------------------------

    // ----- Variable declarations ---------------------------------------------

    // ----- Module instance declarations --------------------------------------

//    hit_generator_tb hit_generator_tb("Hit_Generator_TB");
//    frontend_chip_cbc_tb fechip_cbc_tb("FE_Chip_CBC_TB", trace_file);
//    frontend_chip_mpa_tb fechip_mpa_tb("FE_Chip_MPA_TB", trace_file);
    data_concentrator_cbc_tb data_concentrator_cbc_tb("Data_Concentrator_CBC_TB");
//    data_concentrator_mpa_tb data_concentrator_mpa_tb("Data_Concentrator_MPA_TB");
//    data_organizer_tb data_organizer_tb("Data_Organizer_TB");
//    fifo_manager_tb fifo_manager_tb("FIFO_Manager_TB");
//    fifo_manager_datapath_tb("FIFO_Manager_Datapath_TB");
//	  am_system_tb am_system_tb("AM_System");
//    am_board_tb am_board_tb("AM_board_TB");
//    trigger_tower_tb("trigger_tower_tb");
//    prbf_tb();
//    cic_format_tb();

    // ----- Time unit / resolution setup --------------------------------------

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

//    sc_trace(trace_file, am_system_tb.LHC_clock, "clock");
//    sc_trace(trace_file, am_system_tb.input_fifos[0].stub_out, "FIFO_0.out");
//
//    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].current_state, "FIFO_FSM_0.current_state");
//    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].next_state, "FIFO_FSM_0.next_state");
//    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].fifo_not_empty, "FIFO_FSM_0.fifo_not_empty");
//    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].pop, "FIFO_FSM_0.pop");
//    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].fifo_read_en, "FIFO_FSM_0.fifo_read_en");
//    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].pok, "FIFO_FSM_0.pok");
//    sc_trace(trace_file, am_system_tb.am_ctrl.fifo_fsm_array[0].reg_en, "FIFO_FSM_0.reg_en");
//
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.current_state, "main_FSM.current_state");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.next_state, "main_FSM.next_state");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.pok, "main_FSM.pok");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.hee_reg, "main_FSM.hee_reg");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.finish_road, "main_FSM.finish_road");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.pop, "main_FSM.pop");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.en, "main_FSM.en");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.init_ev, "main_FSM.init_ev");
//    sc_trace(trace_file, am_system_tb.am_ctrl.main_am_fsm.AM_latency_cnt, "main_FSM.latency_count");
//
//    sc_trace(trace_file, am_system_tb.am_ctrl.hit_controller.hit_controllers[0].new_hit, "hit_ctrl_0.new_hit");
//    sc_trace(trace_file, am_system_tb.am_ctrl.hit_controller.hit_controllers[0].hee_reg, "hit_ctrl_0.hee_reg");
//    sc_trace(trace_file, am_system_tb.am_ctrl.hit_controller.hit_controllers[0].wr_hit_lamb, "hit_ctrl_0.wr_hit_lamb");
//    sc_trace(trace_file, am_system_tb.am_ctrl.hit_controller.hit_controllers[0].init_event, "hit_ctrl_0.init_event");
//    sc_trace(trace_file, am_system_tb.am_ctrl.hit_controller.hit_controllers[0].write_en, "hit_ctrl_0.write_en");
//    sc_trace(trace_file, am_system_tb.am_ctrl.hit_controller.hit_controllers[0].stub_output, "hit_ctrl_0.stub_output");
//    sc_trace(trace_file, am_system_tb.am_ctrl.hit_controller.hit_controllers[0].stub_read, "hit_ctrl_0.stub_read");
//
//    sc_trace(trace_file, am_system_tb.am_ctrl.road_controller.data_ready_road, "road_ctrl.data_ready");
//    sc_trace(trace_file, am_system_tb.am_ctrl.road_controller.road_in, "road_ctrl.road_in");
//    sc_trace(trace_file, am_system_tb.am_ctrl.road_controller.write_en_road, "road_ctrl.write_en");
//    sc_trace(trace_file, am_system_tb.am_ctrl.road_controller.road_out, "road_ctrl.road_out");
//    sc_trace(trace_file, am_system_tb.am_ctrl.road_controller.finish_road, "road_ctrl.finish_road");

//    sc_trace(trace_file, fifo_manager_tb.LHC_clock, "clock");
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.controller.current_state, "current_state");
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.time_stamp_sig, "time_stamp_sig");
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.controller.time_stamp_cnt_en, "time_stamp_cnt_en");
//
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.stub_in.at(0,0), "stub_in-0-0");
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.fifo_out.at(0,0), "fifo_out-0-0");
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.fifo_out.at(1,0), "fifo_out-1-0");
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.fifo_out.at(2,0), "fifo_out-2-0");
//    sc_trace(trace_file, fifo_manager_tb.dut_fifo_manager.fifo_out.at(3,0), "fifo_out-3-0");


    // ----- Start simulation --------------------------------------------------

    std::cout << std::endl << "Start test bench ..." << std::endl << std::endl;

    //sc_report_handler::set_actions (SC_ID_MORE_THAN_ONE_SIGNAL_DRIVER_, SC_DO_NOTHING);
    sc_start(1500, SC_NS);

    sc_close_vcd_trace_file(trace_file);
    std::cout << std::endl << "Test bench ended." << std::endl;

    return (0);
}
