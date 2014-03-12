/*!
 * @file TT_TB_top.cpp
 * @author Christian Amstutz
 * @date Mar 12, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <iostream>
#include <sstream>
#include <utility>

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"
#include "../lib/systemc_helpers/sc_analyzer/sc_analyzer.hpp"

#include "TT_configuration.hpp"
#include "hit_generator.hpp"
#include "sensor_module.hpp"
//#include "data_organizer.hpp"

int sc_main(int argc, char *agv[])
{
    sc_analyzer analyzer;
    analyzer.register_model_setup_start();

    // ----- Channel declarations ------------------------------------------------
    sc_clock LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true);

    sc_map_4d<sc_fifo<stub> > hit_fifos(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo", 0, 0, 0, 0);

    sc_map_cube<sc_signal<sc_bv<DC_OUTPUT_WIDTH> > > fe_signals(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "fe_signals", 0, 0, 0);

    // ----- Variable declarations -----------------------------------------------

    // ----- Module instance declarations ----------------------------------------

    hit_generator hitGenerator("Hit_Generator", "hits.txt");
    hitGenerator.hit_outputs.bind(hit_fifos);

    sc_map_cube<sensor_module> sensor_modules(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor-module");
    for (auto& sens_module : sensor_modules)
    {
        sens_module.clk(LHC_clock);

        //* todo: XXX
        //sens_module.stub_inputs(hit_fifos.getLinear(1,2,3));

        std::pair<bool, sc_map_cube<sensor_module>::full_key_type> full_key;
        full_key = sensor_modules.get_key(sens_module);
        sens_module.dc_out.bind(fe_signals.at(full_key.second.Z_dim, full_key.second.Y_dim, full_key.second.X_dim));
    }

    // ----- Time unit / resolution setup ----------------------------------------

    // ----- Set up tracing ------------------------------------------------------

    //* todo: XXX
//  sc_trace_file *trace_file;
//  trace_file=sc_create_vcd_trace_file("TT_TB");
//
//  sc_trace(trace_file, LHC_clock, "LHC_clk");
//
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[0]->hit_outputs[0].dv, "hits_0-0-0-0");
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[1]->hit_outputs[0].dv, "hits_0-0-0-1");
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[2]->hit_outputs[0].dv, "hits_0-0-0-2");
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[3]->hit_outputs[0].dv, "hits_0-0-0-3");
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[4]->hit_outputs[0].dv, "hits_0-0-0-4");
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[5]->hit_outputs[0].dv, "hits_0-0-0-5");
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[6]->hit_outputs[0].dv, "hits_0-0-0-6");
//  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[7]->hit_outputs[0].dv, "hits_0-0-0-7");
//
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[0]->hit_outputs[0].dv, "hits_1-0-0-0");
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[1]->hit_outputs[0].dv, "hits_1-0-0-1");
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[2]->hit_outputs[0].dv, "hits_1-0-0-2");
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[3]->hit_outputs[0].dv, "hits_1-0-0-3");
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[4]->hit_outputs[0].dv, "hits_1-0-0-4");
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[5]->hit_outputs[0].dv, "hits_1-0-0-5");
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[6]->hit_outputs[0].dv, "hits_1-0-0-6");
//  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[7]->hit_outputs[0].dv, "hits_1-0-0-7");
//
//
//  sc_trace(trace_file, *fe_signals[0][0][0],"DC_out_1_1_1");
//  sc_trace(trace_file, *fe_signals[1][0][0],"DC_out_2_1_1");
//  sc_trace(trace_file, *fe_signals[2][0][0],"DC_out_3_1_1");
//  sc_trace(trace_file, *fe_signals[3][0][0],"DC_out_4_1_1");
//  sc_trace(trace_file, *fe_signals[4][0][0],"DC_out_5_1_1");
//  sc_trace(trace_file, *fe_signals[5][0][0],"DC_out_6_1_1");

  // ----- Start simulation ----------------------------------------------------

    #ifdef DEBUG
    std::cout << "Start simulation ..." << std::endl;
    #endif

    analyzer.register_simulation_start();
    sc_start(1000, SC_NS);
    analyzer.register_simulation_end();

//  sc_close_vcd_trace_file(trace_file);

    #ifdef DEBUG
    std::cout << "Simulation ended." << std::endl;
    #endif

    analyzer.print_report();
  
    return (0);
}
