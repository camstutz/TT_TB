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

    sc_map_4d<sc_fifo<stub> > hit_fifos(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo", 1, 1, 1, 1);

    sc_map_cube<sc_signal<sc_bv<DC_OUTPUT_WIDTH> > > fe_signals(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "fe_signals", 1, 1, 1);

    // ----- Variable declarations -----------------------------------------------

    // ----- Module instance declarations ----------------------------------------

    hit_generator hitGenerator("Hit_Generator", "hits.txt");
    hitGenerator.hit_outputs.bind(hit_fifos);

    sc_map_cube<sensor_module> sensor_modules(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor-module", 1, 1, 1);

    for (auto& sens_module : sensor_modules)
    {
        auto full_key = sensor_modules.get_key(sens_module);

        sens_module.clk(LHC_clock);
        auto fifo_it  = hit_fifos.begin_partial(full_key.second.Z_dim, false, full_key.second.Y_dim, false, full_key.second.X_dim, false, 0, true);
        sens_module.stub_inputs.bind_by_iter(fifo_it);
        sens_module.dc_out.bind(fe_signals.at(full_key.second.Z_dim, full_key.second.Y_dim, full_key.second.X_dim));
    }

    // ----- Time unit / resolution setup ----------------------------------------

    // ----- Set up tracing ------------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB");

    sc_trace(trace_file, LHC_clock, "LHC_clk");

    // ----- Start simulation ----------------------------------------------------

    #ifdef DEBUG
    std::cout << "Start simulation ..." << std::endl;
    #endif

    analyzer.register_simulation_start();
    sc_start(1000, SC_NS);
    analyzer.register_simulation_end();

    sc_close_vcd_trace_file(trace_file);

    #ifdef DEBUG
    std::cout << "Simulation ended." << std::endl;
    #endif

    analyzer.print_report();
  
    return (0);
}
