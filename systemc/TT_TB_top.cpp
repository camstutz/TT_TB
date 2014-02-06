/*!
 * @file TT_TB_top.cpp
 * @author Christian Amstutz
 * @date Feb 6, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <iostream>
#include <sstream>
#include <array>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "hit_generator.hpp"
#include "sensor_module.hpp"
//#include "data_organizer.hpp"

int sc_main(int argc, char *agv[]) {

  // ----- Channel declarations ------------------------------------------------
  sc_clock LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true);

  typedef std::array<sc_fifo<stub>*, NR_FE_CHIP_PER_MODULE> stub_fifo_module_t;
  typedef std::array<stub_fifo_module_t, NR_DETECTOR_Z> stub_fifo_line_t;
  typedef std::array<stub_fifo_line_t, NR_DETECTOR_PHI> stub_fifo_layer_t;
  typedef std::array<stub_fifo_layer_t, NR_DETECTOR_LAYERS> stub_fifo_detector_t;
  stub_fifo_detector_t hit_fifos;
  unsigned int layer_cnt = 0;
  for (stub_fifo_layer_t &stubs_layer : hit_fifos) {
    unsigned int phi_cnt = 0;
    for (stub_fifo_line_t &stubs_line : stubs_layer) {
      unsigned int z_cnt = 0;
      for (stub_fifo_module_t &stubs_module : stubs_line) {
        unsigned int fe_cnt = 0;
        for (sc_fifo<stub>* &stub_fifo : stubs_module) {
          std::ostringstream fifo_name;
          fifo_name << "stub_fifo_L" << layer_cnt+1
                    << "P" << phi_cnt+1
                    << "Z" << z_cnt+1
                    << "F" << fe_cnt+1;
          stub_fifo = new sc_fifo<stub>(fifo_name.str().c_str());

          ++fe_cnt;
        }
        ++z_cnt;
      }
      ++phi_cnt;
    }
    ++layer_cnt;
  }

  typedef std::array<sc_signal<sc_bv<DC_OUTPUT_WIDTH> >*, NR_DETECTOR_Z> dc_out_line_t;
  typedef std::array<dc_out_line_t, NR_DETECTOR_PHI> dc_out_layer_t;
  typedef std::array<dc_out_layer_t, NR_DETECTOR_LAYERS> dc_out_detector_t;
  dc_out_detector_t fe_signals;
  layer_cnt = 0;
  for (dc_out_layer_t &fe_layer : fe_signals) {
    unsigned int phi_cnt = 0;
    for (dc_out_line_t &fe_line : fe_layer) {
      unsigned int z_cnt = 0;
      for (sc_signal<sc_bv<DC_OUTPUT_WIDTH> >* &dc_out_sig : fe_line) {
        std::ostringstream signal_name;
        signal_name << "dc_out_L" << layer_cnt+1
                    << "P" << phi_cnt+1
                    << "Z" << z_cnt+1;
        dc_out_sig = new sc_signal<sc_bv<DC_OUTPUT_WIDTH> >(signal_name.str().c_str());
        ++z_cnt;
      }
      ++phi_cnt;
    }
    ++layer_cnt;
  }

  // ----- Variable declarations -----------------------------------------------

  // ----- Module instance declarations ----------------------------------------

  hit_generator hitGenerator("Hit_Generator", "hits.txt");
  layer_cnt = 0;
  for (hit_generator::layer_dim_out_t &hit_layer : hitGenerator.hit_outputs) {
    unsigned int phi_cnt = 0;
    for (hit_generator::phi_dim_out_t &hit_phi: hit_layer) {
      unsigned int z_cnt = 0;
      for (hit_generator::z_dim_out_t &hit_z: hit_phi) {
        unsigned int fe_cnt = 0;
        for (hit_generator::hit_out_t &hit_out : hit_z) {
          hit_out->bind(*hit_fifos[layer_cnt][z_cnt][z_cnt][fe_cnt]);
          ++fe_cnt;
        }
        ++z_cnt;
      }
      ++phi_cnt;
    }
    ++layer_cnt;
  }

  typedef std::array<sensor_module*, NR_DETECTOR_Z> sensor_line_t;
  typedef std::array<sensor_line_t, NR_DETECTOR_PHI> sensor_layer_t;
  typedef std::array<sensor_layer_t, NR_DETECTOR_LAYERS> sensor_detector_t;
  sensor_detector_t sensor_modules;
  layer_cnt = 0;
  for (sensor_layer_t &cylinder: sensor_modules) {
    unsigned int phi_cnt = 0;
    for (sensor_line_t &line : cylinder) {
      unsigned int z_cnt = 0;
      for (sensor_module* &module : line) {
        std::ostringstream module_name;
        module_name << "sensor_module_L" << layer_cnt+1
                    << "P" << phi_cnt+1
                    << "Z" << z_cnt+1;
        module = new sensor_module(module_name.str().c_str());
        module->clk(LHC_clock);

        unsigned int fe_cnt = 0;
        for (sensor_module::stub_in_t* &stub_input : module->stub_inputs) {
          stub_input->bind(*hit_fifos[layer_cnt][phi_cnt][z_cnt][fe_cnt]);
          ++fe_cnt;
        }
        module->dc_out.bind(*fe_signals[layer_cnt][phi_cnt][z_cnt]);
        ++z_cnt;
      }
      ++phi_cnt;
    }
    ++layer_cnt;
  }

  // ----- Time unit / resolution setup ----------------------------------------

  // ----- Set up tracing ------------------------------------------------------
  sc_trace_file *trace_file;
  trace_file=sc_create_vcd_trace_file("TT_TB");

  sc_trace(trace_file, LHC_clock, "LHC_clk");

  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[0]->hit_outputs[0].dv, "hits_0-0-0-0");
  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[1]->hit_outputs[0].dv, "hits_0-0-0-1");
  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[2]->hit_outputs[0].dv, "hits_0-0-0-2");
  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[3]->hit_outputs[0].dv, "hits_0-0-0-3");
  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[4]->hit_outputs[0].dv, "hits_0-0-0-4");
  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[5]->hit_outputs[0].dv, "hits_0-0-0-5");
  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[6]->hit_outputs[0].dv, "hits_0-0-0-6");
  sc_trace(trace_file, *sensor_modules[0][0][0]->front_end_chips[7]->hit_outputs[0].dv, "hits_0-0-0-7");

  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[0]->hit_outputs[0].dv, "hits_1-0-0-0");
  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[1]->hit_outputs[0].dv, "hits_1-0-0-1");
  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[2]->hit_outputs[0].dv, "hits_1-0-0-2");
  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[3]->hit_outputs[0].dv, "hits_1-0-0-3");
  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[4]->hit_outputs[0].dv, "hits_1-0-0-4");
  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[5]->hit_outputs[0].dv, "hits_1-0-0-5");
  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[6]->hit_outputs[0].dv, "hits_1-0-0-6");
  sc_trace(trace_file, *sensor_modules[1][0][0]->front_end_chips[7]->hit_outputs[0].dv, "hits_1-0-0-7");


  sc_trace(trace_file, *fe_signals[0][0][0],"DC_out_1_1_1");
  sc_trace(trace_file, *fe_signals[1][0][0],"DC_out_2_1_1");
  sc_trace(trace_file, *fe_signals[2][0][0],"DC_out_3_1_1");
  sc_trace(trace_file, *fe_signals[3][0][0],"DC_out_4_1_1");
  sc_trace(trace_file, *fe_signals[4][0][0],"DC_out_5_1_1");
  sc_trace(trace_file, *fe_signals[5][0][0],"DC_out_6_1_1");

  // ----- Start simulation ----------------------------------------------------

  #ifdef DEBUG
  std::cout << "Start simulation ..." << std::endl;
  #endif

  sc_start(1000, SC_NS);
  sc_close_vcd_trace_file(trace_file);

  #ifdef DEBUG
  std::cout << "Simulation ended." << std::endl;
  #endif
  
  return 0;
}
