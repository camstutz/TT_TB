/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date July 17, 2015
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
#include "hit_generator_tb.hpp"
#include "frontend_chip_cbc_tb.hpp"
#include "frontend_chip_mpa_tb.hpp"
#include "data_concentrator_cbc_tb.hpp"
#include "data_concentrator_mpa_tb.hpp"
//#include "gbt_tb.hpp"
//#include "dtc_input_unit_tb.hpp"
//#include "dtc_output_unit_tb.hpp"
//#include "dtc_tb.hpp"
//#include "backend_common/bx_stub_buffer_tb.hpp"
//#include "backend_common/input_collector_tb.hpp"
//#include "backend_common/time_demux_tb.hpp"
//#include "data_organizer/data_organizer_tb.hpp"
//#include "processor_organizer/po_layer_splitter_tb.hpp"
//#include "processor_organizer/processor_organizer_tb.hpp"
//#include "am_board/am_input_module_one_layer_tb.hpp"
//#include "am_board/am_input_module_tb.hpp"
//#include "track_finder/am_chip_tb.hpp"
//#include "track_finder/pattern_bank_tb.hpp"
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


    // ----- Channel declarations ----------------------------------------------

    // ----- Variable declarations ---------------------------------------------

    // ----- Module instance declarations --------------------------------------

    configuration.hit_generator.input_file = "/home/chris/eclipse/git/TT_TB/source/systemc/module_tests/test_hits.txt";

//    hit_generator_tb hit_generator_tb("Hit_Generator_TB", configuration);
    frontend_chip_cbc_tb fechip_cbc_tb("FE_Chip_CBC_TB", trace_file, configuration);
//    frontend_chip_mpa_tb fechip_mpa_tb("FE_Chip_MPA_TB", trace_file, configuration);
//    data_concentrator_cbc_tb data_concentrator_cbc_tb("Data_Concentrator_CBC_TB", configuration);
//    data_concentrator_mpa_tb data_concentrator_mpa_tb("Data_Concentrator_MPA_TB", configuration);
//    gbt_config gbt_configuration;
//    gbt_configuration.input_link_count = 2;
//    gbt_tb gbt_TB("GBT_TB", gbt_configuration, configuration.cbc_data_concentrator);
//    dtc_input_unit_tb dtc_INU_TB("DTC_input_unit_TB", configuration);
//    dtc_output_unit_tb dtc_OUTU_TB("DTC_output_unit_TB", configuration);
//    dtc_tb DTC_TB("DTC_TB", configuration);
//
//    bx_stub_buffer_tb bx_stub_buffer_TB("bx_stub_buffer_TB");
//    input_collector_tb do_input_collector_TB("DO_input_collector_TB", configuration.trigger_tower.data_organizer.input_collector);
//    time_demux_tb do_demux_TB("DO_dmux_TB", configuration.trigger_tower.data_organizer.demultiplexer);
//    data_organizer_tb data_organizer_tb("Data_Organizer_TB", configuration);
//    po_layer_splitter_tb PO_layer_splitter_TB("PO_layer_splitter_TB", configuration.trigger_tower.processor_organizer.layer_splitter);
//    processor_organizer_tb processor_organizer_TB("processor_organizer_TB", configuration);
//    am_input_module_one_layer_tb am_in_mod_one_layer_TB("AM_input_module_one_layer_TB");
//    am_input_module_tb am_in_mod_TB("AM_input_module_TB", configuration);
//      pattern_bank_tb();
//    am_chip_tb AMchip_TB("AMchip_TB", configuration);
//    trigger_tower_tb triggerTower_TB("trigger_tower_TB", configuration);
//    prbf_tb();
//    cic_format_tb();

    // ----- Time unit / resolution setup --------------------------------------

    sc_trace(trace_file, fechip_cbc_tb.LHC_clock, "clock");
    sc_trace(trace_file, fechip_cbc_tb.dut_front_end_chip.delay_data_valid[0].read_ptr, "read_ptr");
    sc_trace(trace_file, fechip_cbc_tb.dut_front_end_chip.delay_data_valid[0].write_ptr, "write_ptr");
    sc_trace(trace_file, fechip_cbc_tb.dut_front_end_chip.delay_data_valid[0].data_valid_buffer[0], "buffer(0)");
    //sc_trace(trace_file, fechip_mpa_tb.dut_front_end_chip.delay_data_valid[0].data_valid_buffer[1], "buffer(1)");
    sc_trace(trace_file, fechip_cbc_tb.dut_front_end_chip.delay_data_valid[0].input, "dv_input");
    sc_trace(trace_file, fechip_cbc_tb.dut_front_end_chip.delay_data_valid[0].delayed, "dv_delayed");

    // ----- Start simulation --------------------------------------------------

    std::cout << std::endl << "Start test bench ...." << std::endl << std::endl;

    //sc_report_handler::set_actions (SC_ID_MORE_THAN_ONE_SIGNAL_DRIVER_, SC_DO_NOTHING);
    sc_start(1000, SC_NS);

    sc_close_vcd_trace_file(trace_file);
    std::cout << std::endl << "Test bench ended!" << std::endl;

    return (0);
}
