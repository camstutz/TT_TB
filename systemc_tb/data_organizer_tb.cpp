/*!
 * @file data_organizer_tb.cpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
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
        do_output(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "do_output"),
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
        do_output.make_sensitive(sensitive);

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
    test_value = ( (sc_bv<2>(2), sc_bv<30>(0x8008FFFF)) );
    fe_streams[1].write(test_value);

    wait();
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x0)) );
    fe_streams[0].write(test_value);
    test_value = ( (sc_bv<2>(0), sc_bv<30>(0x00000200)) );
    fe_streams[1].write(test_value);

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

    return;
}

// *****************************************************************************
void data_organizer_tb::print_output()
{
    while(1)
    {
        wait();

        for (auto& outport : do_output)
        {
            auto output_data = outport.read();
            if (output_data.get_dv())
            {
                auto key = do_output.get_key(outport);
                unsigned int layer = key.second.Y_dim;
                unsigned int port = key.second.X_dim;
                log_buffer << sc_time_stamp()
                    << " (Layer=" << layer << ",Port=" << port  <<"): "
                    << output_data << std::endl;
            }
        }
    }

}
