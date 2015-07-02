/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date April 22, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include <systemc.h>
#include <iostream>
#include <string>

#include "../TT_configuration/track_trigger_config.hpp"
#include "../TT_configuration/baseline_config.hpp"

#include "../systems/tt_tb_logger.hpp"

//#include "hit_file_test.hpp"
//#include "hit_generator_tb.hpp"
#include "frontend_chip_cbc_tb.hpp"
#include "frontend_chip_mpa_tb.hpp"
#include "data_concentrator_cbc_tb.hpp"
#include "data_concentrator_mpa_tb.hpp"
#include "gbt_tb.hpp"
//#include "dtc_input_unit_tb.hpp"
//#include "dtc_output_unit_tb.hpp"
//#include "dtc_tb.hpp"
#include "backend_common/bx_stub_buffer_tb.hpp"
#include "backend_common/input_collector_tb.hpp"
//#include "backend_common/time_demux_tb.hpp"
//#include "data_organizer/data_organizer_tb.hpp"
//#include "processor_organizer/po_layer_splitter_tb.hpp"
//#include "processor_organizer/processor_organizer_tb.hpp"
//#include "am_board/am_input_module_one_layer_tb.hpp"
//#include "am_board/am_input_module_tb.hpp"
//#include "track_finder/am_chip_tb.hpp"
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

    track_trigger_config configuration = baseline_config();

    gbt_config gbt_configuration;
    gbt_configuration.input_link_count = 2;

    input_collector_config in_collector_configuration;
    in_collector_configuration.input_nr = 1;

    // ----- Channel declarations ----------------------------------------------

    // ----- Variable declarations ---------------------------------------------

    // ----- Module instance declarations --------------------------------------

//    hit_generator_tb hit_generator_tb("Hit_Generator_TB");
//    frontend_chip_cbc_tb fechip_cbc_tb("FE_Chip_CBC_TB", trace_file, configuration);
//    frontend_chip_mpa_tb fechip_mpa_tb("FE_Chip_MPA_TB", trace_file, configuration);
//    data_concentrator_cbc_tb data_concentrator_cbc_tb("Data_Concentrator_CBC_TB", configuration);
//    data_concentrator_mpa_tb data_concentrator_mpa_tb("Data_Concentrator_MPA_TB", configuration);
//    gbt_tb gbt_TB("GBT_TB", gbt_configuration);
//    dtc_input_unit_tb dtc_INU_TB("DTC_input_unit_TB");
//    dtc_output_unit_tb dtc_OUTU_TB("DTC_output_unit_TB");
//    dtc_tb DTC_TB("DTC_TB");
    bx_stub_buffer_tb bx_stub_buffer_TB("bx_stub_buffer_TB");
    input_collector_tb do_input_collector_TB("DO_input_collector_TB", in_collector_configuration);
//    time_demux_tb do_demux_TB("DO_dmux_TB");
//    data_organizer_tb data_organizer_tb("Data_Organizer_TB");
//    po_layer_splitter_tb PO_layer_splitter_TB("PO_layer_splitter_TB");
//    processor_organizer_tb processor_organizer_TB("processor_organizer_TB");
//    fifo_manager_tb fifo_manager_tb("FIFO_Manager_TB");
//    fifo_manager_datapath_tb("FIFO_Manager_Datapath_TB");
//    am_input_module_one_layer_tb am_in_mod_one_layer_TB("AM_input_module_one_layer_TB");
//    am_input_module_tb am_in_mod_TB("AM_input_module_TB");
//	  am_system_tb am_system_tb("AM_System");
//    am_board_tb am_board_tb("AM_board_TB");
//    am_chip_tb AMchip_TB("AMchip_TB");
//    trigger_tower_tb triggerTower_TB("trigger_tower_TB");
//    prbf_tb();
//    cic_format_tb();

    // ----- Time unit / resolution setup --------------------------------------

//    sc_trace(trace_file, am_in_mod_TB.dut_am_input_module_tb.controller.clk, "clk");
//    sc_trace(trace_file, am_in_mod_TB.dut_am_input_module_tb.controller.current_state, "current_state");
//    sc_trace(trace_file, am_in_mod_TB.dut_am_input_module_tb.controller.frame_available, "frame_available");
//    sc_trace(trace_file, am_in_mod_TB.dut_am_input_module_tb.controller.frame_empty, "frame_empty");
//    sc_trace(trace_file, am_in_mod_TB.dut_am_input_module_tb.controller.init_processing, "init_processing");
//    sc_trace(trace_file, am_in_mod_TB.dut_am_input_module_tb.controller.delete_frame, "delete_frame");

//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.processorOrganizers[0]->do_inputs, "PO0_DO_in");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.processorOrganizers[1]->do_inputs, "PO1_DO_in");
    //sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(0,0).TrackFinder.hit_input, "AM0_frame_input");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).TrackFinder.hit_input, "AM1_frame_input");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).AM_InputModule.controller.clk, "clk");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).AM_InputModule.controller.current_state, "current_state");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).AM_InputModule.controller.frame_available, "frame_available");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).AM_InputModule.controller.frame_empty, "frame_empty");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).AM_InputModule.controller.init_processing, "init_processing");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).AM_InputModule.controller.delete_frame, "delete_frame");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).AM_InputModule.stub_stream_outputs, "stub_stream_output");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).TrackFinder.road_lookup.write_controller.current_state, "AM_chip.write.current_state");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).TrackFinder.road_lookup.read_controller.current_state, "AM_chip.read.current_state");
//    sc_trace(trace_file, triggerTower_TB.dut_trigger_tower.amBoards.at(1,1).TrackFinder.road_lookup.hit_inputs, "AM_chip.input");

//    sc_trace(trace_file, AMchip_TB.dut_AM_chip.clk, "clk");
//    sc_trace(trace_file, AMchip_TB.dut_AM_chip.hit_inputs, "AM_chip.input");
//    sc_trace(trace_file, AMchip_TB.dut_AM_chip.write_controller.current_state, "write_ctrl.current_state");
//    sc_trace(trace_file, AMchip_TB.dut_AM_chip.read_controller.current_state, "read_ctrl.current_state");

    // ----- Start simulation --------------------------------------------------

    std::cout << std::endl << "Start test bench ..." << std::endl << std::endl;

    //sc_report_handler::set_actions (SC_ID_MORE_THAN_ONE_SIGNAL_DRIVER_, SC_DO_NOTHING);
    sc_start(2000, SC_NS);

    sc_close_vcd_trace_file(trace_file);
    std::cout << std::endl << "Test bench ended!" << std::endl;

    return (0);
}
