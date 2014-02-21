/*!
 * @file data_concentrator.cpp
 * @author Christian Amstutz
 * @date Feb 20, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_concentrator.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class data_concentrator
 *
 * The module is sensitive to ....
 */

data_concentrator::data_concentrator(sc_module_name _name) :
        sc_module(_name) ,
        clk("clk"),
        rst("rst"),
        fe_stub_in(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_FE_CHIP, "stub_in"),
        dc_out("dc_out"),
        empty_slot( (false, sc_bv<19>(0)) )
{
    // ----- Process registration ------------------------------------------------
    SC_THREAD(advance_clock_phase);
        sensitive << clk.pos();
    SC_THREAD(read_FE_chips);
        sensitive << clk.pos();
    SC_THREAD(write_output);
        sensitive << clk.pos();

    // ----- Module variable initialization --------------------------------------
    clock_phase = 0;

    // ----- Module instance / channel binding -----------------------------------

    // Create and name the input ports
    unsigned int fe_cnt = 0;

    return;
}

// *****************************************************************************
void data_concentrator::read_FE_chips()
{
    while(1)
    {
        wait();

        unsigned int fe_cnt=0;
        for (fe_port_t &fe_port : fe_stub_in) {
            for (fe_in_t &fe_in : fe_port) {
                if (fe_in.dv->read() == true) {
                    //! todo: make generic
                    sc_bv<20> data_word;
                    data_word = ( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(fe_cnt), fe_in.data->read().getBitVector()) );
                    stub_buffer.push_back(data_word);
                }
            }
            fe_cnt++;
        }
    }

}

// *****************************************************************************
void data_concentrator::advance_clock_phase()
{
    while (1)
    {
        wait();

        if (clock_phase.read() == NR_DC_WINDOW_CYCLES-1)
        {
            clock_phase.write(0);
        }
        else
        {
            clock_phase.write(clock_phase.read()+1);
        }

        if (clock_phase.read() == NR_DC_WINDOW_CYCLES-1)
        {
            create_output_buffer();
        }
    }

}

// *****************************************************************************
void data_concentrator::write_output() {

  //! todo: change constants numbers to parameter
  while(1) {
    wait();

    sc_bv<DC_OUTPUT_WIDTH> output_val;
    unsigned int high_buffer = (clock_phase.read()+1)*(DC_OUTPUT_WIDTH-2)-1;
    unsigned int low_buffer = clock_phase.read()*(DC_OUTPUT_WIDTH-2);
    output_val(DC_OUTPUT_WIDTH-3,0) = output_buffer(high_buffer, low_buffer);
    output_val[DC_OUTPUT_WIDTH-2] = 0;
    // Indicate the beginning of a window by the first bit of a data word
    if (clock_phase.read() == 0) {
      output_val[DC_OUTPUT_WIDTH-1] = 1;
    }
    else {
      output_val[DC_OUTPUT_WIDTH-1] = 0;
    }
    dc_out.write(output_val);
  }

}

// *****************************************************************************
void data_concentrator::create_output_buffer() {

  output_buffer = sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES>(0);

  // Buffer size is only NR_DC_OUT_STUBS in real system
  if (stub_buffer.size() > NR_DC_OUT_STUBS) {
    std::cout << "data_concentrator: Stub buffer overflow!" << std::endl;
  }
  stub_buffer.resize(NR_DC_OUT_STUBS, empty_slot);

  for(unsigned short i; i<NR_DC_OUT_STUBS; i++) {
    //! todo: change stub length to constant
    output_buffer( (i+1)*20-1, i*20) = stub_buffer[i];
  }

  stub_buffer.clear();

  return;
}
