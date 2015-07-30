/*!
 * @file gbt_tb.cpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "gbt_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class gbt_tb
 * The module is sensitive to ...
 */

gbt_tb::gbt_tb(sc_module_name _name, gbt_config configuration,
        data_concentrator_config CBC_concentrator_config) :
        sc_module(_name),
        input_streams(2, "input_streams"),
        optical_link("optical_link"),
        gbt_dut("GBT_CBC_DUT", configuration),
        dut_configuration(configuration),
        CBC_concentrator_config(CBC_concentrator_config)
{
    // ----- Creation and binding of signals -----------------------------------
    gbt_dut.cic_in.bind(input_streams);
    gbt_dut.optical_link.bind(optical_link);


    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_cic_data);
    SC_THREAD(print_output);
        sensitive << optical_link;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of GBT-CBC TB:" << std::endl
            << "**********************************************" << std::endl;

    return;
}

// *****************************************************************************
gbt_tb::~gbt_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void gbt_tb::generate_cic_data()
{
    wait(50, SC_NS);

    gbt::input_t test_frame(CBC_concentrator_config.output_stub);
    CIC::header frame_header(CIC::header::CBC, CIC::header::status_OK, 8);
    test_frame.set_header(frame_header);

    // bunch_crossing_t, fe_chip_ID_t, strip_t, bend_t
    //stub_config configuration,
   //             const valid_t valid, const bx_t bx,
    //            const fechip_t fechip, const strip_t strip, const bend_t bend,
    //            const pixel_t pixel

    stub new_stub(CBC_concentrator_config.output_stub, 0, 0, 1, 2, 1, 0);
    test_frame.add_stub(new_stub);
    new_stub = stub(CBC_concentrator_config.output_stub, 0, 0, 1, 2, 2, 0);
    test_frame.add_stub(new_stub);

    input_streams[0].write(test_frame);

    wait(177, SC_NS);
    new_stub = stub(CBC_concentrator_config.output_stub, 0, 0, 1, 2, 3, 0);
    test_frame.add_stub(new_stub);
    input_streams[0].write(test_frame);
    new_stub = stub(CBC_concentrator_config.output_stub, 0, 0, 1, 2, 4, 0);
    test_frame.add_stub(new_stub);
    input_streams[1].write(test_frame);

    wait(1000, SC_NS);

    return;
}

// *****************************************************************************
void gbt_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;
         log_buffer << optical_link.read() << std::endl;
    }
}
