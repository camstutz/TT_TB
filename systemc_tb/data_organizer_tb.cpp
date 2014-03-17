/*!
 * @file data_organizer_tb.cpp
 * @author Christian Amstutz
 * @date Mar 14, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_organizer_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

data_organizer_tb::data_organizer_tb(sc_module_name _name) :
        sc_module(_name),
        rst("rst"),
        fe_streams(NR_DETECTOR_LAYERS, "fe_streams"),
        do_output(NR_DO_OUT_STUBS, "do_output"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_data_organizer("Data_Organizer_DUT", 1, 1)
{
    // ----- Creation and binding of signals -----------------------------------
    dut_data_organizer.clk(LHC_clock);
    dut_data_organizer.rst(rst);
    dut_data_organizer.stream_in.bind(fe_streams);
    dut_data_organizer.stub_out.bind(do_output);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_stream);
        sensitive << LHC_clock.posedge_event();
    SC_THREAD(print_output);
        sensitive << do_output[0];

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

  log_buffer << std::endl
             << "Simulation Output of Data Organizer TB:" << std::endl
             << "***************************************" << std::endl;

  return;
}

// *****************************************************************************

data_organizer_tb::~data_organizer_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void data_organizer_tb::write_stream()
{
    sc_bv<DC_OUTPUT_WIDTH> test_value;

    wait();
    wait();
    test_value = ( (sc_bv<2>(2), sc_bv<30>(0x8008FFFF)) );
    fe_streams[0].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x00000200)) );
    fe_streams[0].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x0)) );
    fe_streams[0].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x0)) );
    fe_streams[0].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x0)) );
    fe_streams[0].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x0)) );
    fe_streams[0].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x0)) );
    fe_streams[0].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x0)) );
    fe_streams[0].write(test_value);

//    wait();
//    test_value = ( (sc_bv<2>(2), sc_bv<30>(255)) );
//    fe_streams[0].write(test_value);
//
//    wait();
//    test_value = ( (sc_bv<2>(0), sc_bv<30>(512)) );
//    fe_streams[0].write(test_value);
//
//    wait();
//    test_value = ( (sc_bv<2>(0), sc_bv<30>(1023)) );
//    fe_streams[0].write(test_value);
//
//    wait();
//    test_value = ( (sc_bv<2>(0), sc_bv<30>(64)) );
//    fe_streams[0].write(test_value);
//
//    wait();
//    test_value = ( (sc_bv<2>(0), sc_bv<30>(12)) );
//    fe_streams[0].write(test_value);
//
//    wait();
//    test_value = ( (sc_bv<2>(0), sc_bv<30>(2047)) );
//    fe_streams[0].write(test_value);
//
//    wait();
//    test_value = ( (sc_bv<2>(0), sc_bv<30>(12)) );
//    fe_streams[0].write(test_value);
//
//    wait();
//    test_value = ( (sc_bv<2>(0), sc_bv<30>(2047)) );
//    fe_streams[0].write(test_value);

    return;
}

// *****************************************************************************
void data_organizer_tb::print_output()
{
  while(1)
  {
    wait();

    log_buffer << sc_time_stamp() << ": " << do_output[0].read() << std::endl;
    log_buffer << "        " << do_output[1].read() << std::endl;
    log_buffer << "        " << do_output[2].read() << std::endl;
    log_buffer << "        " << do_output[3].read() << std::endl;
    log_buffer << "        " << do_output[4].read() << std::endl;
    log_buffer << "        " << do_output[5].read() << std::endl;
  }

}
