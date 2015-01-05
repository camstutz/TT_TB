/*!
 * @file data_organizer_tb.cpp
 * @author Christian Amstutz
 * @date July 31, 2014
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
        dv(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "dv"),
        do_output(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "do_output"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_data_organizer("Data_Organizer_DUT", 1, 1)
{
    // ----- Creation and binding of signals -----------------------------------
    dut_data_organizer.clk.bind(LHC_clock);
    dut_data_organizer.stream_in.bind(fe_streams);
    dut_data_organizer.dv.bind(dv);
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
    // todo: detailed tests of the data organizer timing

    data_organizer::do_in_t test_value;

    wait();
    wait();
    test_value.set_header(2);
    test_value.set_payload(0x00083FFF);
    fe_streams[3].write(test_value);

    wait();
    test_value.set_header(0);
    test_value.set_payload(0x00000000);
    fe_streams[3].write(test_value);
    test_value.set_header(0);
    test_value.set_payload(0x30FFFC00);
    fe_streams[4].write(test_value);

    wait();
    test_value.set_header(0);
    test_value.set_payload(0x00000000);
    fe_streams[4].write(test_value);

    test_value.set_header(0);
    test_value.set_payload(0x00000000);
    fe_streams[0].write(test_value);

    wait();
    wait();
    wait();
    test_value.set_header(2);
    test_value.set_payload(0x3F8F3FFF);
    fe_streams[1].write(test_value);

    wait();
    test_value.set_header(0);
    test_value.set_payload(0x00027D7F);
    fe_streams[1].write(test_value);

    wait();
    test_value.set_header(0);
    test_value.set_payload(0x00000000);
    fe_streams[1].write(test_value);

    return;
}

// *****************************************************************************
void data_organizer_tb::print_output()
{
    while(1)
    {
        wait();

        unsigned int out_cnt = 0;
        for (auto& outport : do_output)
        {
            unsigned int layer = out_cnt/NR_DO_OUT_STUBS;
            unsigned int stub_nr = out_cnt%NR_DO_OUT_STUBS;
            if (dv.at(layer, stub_nr).read() == true)
            {
                auto output_data = outport.read();
                auto key = do_output.get_key(outport);
                unsigned int layer = key.second.Y_dim;
                unsigned int port = key.second.X_dim;
                log_buffer << sc_time_stamp()
                    << " (Layer=" << layer << ",Port=" << port  <<"): "
                    << output_data << std::endl;
            }
            ++out_cnt;
        }
    }

}
