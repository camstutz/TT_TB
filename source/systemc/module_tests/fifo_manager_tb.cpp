/*!
 * @file fifo_manager_tb.cpp
 * @author Christian Amstutz
 * @date Sep 18, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_manager_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class fifo_manager_tb
 * The module is sensitive to ...
 */

fifo_manager_tb::fifo_manager_tb(sc_module_name _name) :
        sc_module(_name),
        rst("rst"),
        dv_inputs(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "dv_input"),
        stub_inputs(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "stub_input"),
        neighbour_dv_inputs(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS,"neigh_dv_input"),
        neighbour_stub_inputs(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS,"neigh_stub_input"),
        neighbour_dv_outputs(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS,"neigh_dv_output"),
        neighbour_stub_outputs(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS,"neigh_stub_output"),
        dv_outputs(NR_AM_BOARDS, NR_DETECTOR_LAYERS, "dv_output"),
        fifo_outputs(NR_AM_BOARDS, NR_DETECTOR_LAYERS, "fifo_output"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_fifo_manager("FIFO_Manager_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_fifo_manager.clk.bind(LHC_clock);
    dut_fifo_manager.rst.bind(rst);
    dut_fifo_manager.dv_in.bind(dv_inputs);
    dut_fifo_manager.stub_in.bind(stub_inputs);
    dut_fifo_manager.neighbour_dv_in.bind(neighbour_dv_inputs);
    dut_fifo_manager.neighbour_stub_in.bind(neighbour_stub_inputs);
    dut_fifo_manager.neighbour_dv_out.bind(neighbour_dv_outputs);
    dut_fifo_manager.neighbour_stub_out.bind(neighbour_stub_outputs);
    dut_fifo_manager.dv_out.bind(dv_outputs);
    dut_fifo_manager.fifo_out.bind(fifo_outputs);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_input);
    SC_THREAD(print_output);
        sensitive << LHC_clock.posedge_event();
        //fifo_outputs.make_sensitive(sensitive);
        //neigh_dv_output;
        //neigh_stub_output;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of FIFO Manager TB:" << std::endl
            << "*******************************************" << std::endl;

    return;
}

// *****************************************************************************
fifo_manager_tb::~fifo_manager_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void fifo_manager_tb::generate_input()
{
    fifo_manager::input_stub_t stub;

    wait(25, SC_NS);
    stub = fifo_manager::input_stub_t(0,0,1,1);
    dv_inputs.at(0,0).write(true);
    stub_inputs.at(0,0).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,2);
    dv_inputs.at(0,1).write(true);
    stub_inputs.at(0,1).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,3);
    dv_inputs.at(0,2).write(true);
    stub_inputs.at(0,2).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,4);
    dv_inputs.at(0,3).write(true);
    stub_inputs.at(0,3).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,5);
    dv_inputs.at(0,4).write(true);
    stub_inputs.at(0,4).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,6);
    dv_inputs.at(0,5).write(true);
    stub_inputs.at(0,5).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,7);
    dv_inputs.at(0,6).write(true);
    stub_inputs.at(0,6).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,8);
    dv_inputs.at(0,7).write(true);
    stub_inputs.at(0,7).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,9);
    dv_inputs.at(0,8).write(true);
    stub_inputs.at(0,8).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,10);
    dv_inputs.at(0,9).write(true);
    stub_inputs.at(0,9).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,11);
    dv_inputs.at(0,10).write(true);
    stub_inputs.at(0,10).write(stub);
    stub = fifo_manager::input_stub_t(0,0,1,12);
    dv_inputs.at(1,11).write(true);
    stub_inputs.at(1,11).write(stub);
    stub = fifo_manager::input_stub_t(1,0,0,12);
    neighbour_dv_inputs.at(0,0).write(true);
    neighbour_stub_inputs.at(0,0).write(stub);

    wait(100, SC_NS);
    stub = fifo_manager::input_stub_t();
    dv_inputs.write_all(false);
    stub_inputs.write_all(stub);
    neighbour_dv_inputs.write_all(false);
    neighbour_stub_inputs.write_all(stub);

//    wait(100, SC_NS);
//    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,1));
//    stub_inputs.at(0,0).write(stub);
//    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,2));
//    stub_inputs.at(0,1).write(stub);
//    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,3));
//    stub_inputs.at(0,2).write(stub);
//    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,4));
//    stub_inputs.at(0,3).write(stub);
//
//    wait(100, SC_NS);
//    stub = do_out_data(false, do_out_data::do_stub_t(0,0,0,0));
//    stub_inputs.write_all(stub);
//
//    wait(100, SC_NS);
//    stub = do_out_data(true, do_out_data::do_stub_t(2,2,0,20));
//    stub_inputs.at(0,0).write(stub);
//
//    wait(100, SC_NS);
//    stub = do_out_data(false, do_out_data::do_stub_t(0,0,0,0));
//    stub_inputs.write_all(stub);

    return;
}

// *****************************************************************************
void fifo_manager_tb::print_output()
{
    while(1)
    {
         wait();

         // Check FIFO outputs
         auto fifo_out_it = fifo_outputs.begin();
         auto dv_out_it = dv_outputs.begin();

         for (; fifo_out_it != fifo_outputs.end(); ++fifo_out_it)
         {
             if (dv_out_it->read() == true)
             {
                 fm_out_data value = fifo_out_it->read();

                 auto out_key = fifo_outputs.get_key(*fifo_out_it);
                 auto lane = out_key.second.Y_dim;
                 auto layer = out_key.second.X_dim;

                 if (value.is_timestamp())
                 {
                     log_buffer << sc_time_stamp() << " (Lane=" << lane << ",Lay=" << layer << "): ";
                     log_buffer << " TS=" << value.get_timestamp() << std::endl;
                 }
                 else
                 {
                     log_buffer << sc_time_stamp() << " (Lane=" << lane << ",Lay=" << layer << "): ";
                     log_buffer << value.get_data_stub() << std::endl;
                 }
             }

             ++dv_out_it;
         }

         // Check neighbour outputs
         auto neighbour_out_it = neighbour_stub_outputs.begin();
         auto neighbour_dv_it = neighbour_dv_outputs.begin();

         for (; neighbour_out_it != neighbour_stub_outputs.end(); ++neighbour_out_it)
         {
             if (neighbour_dv_it->read() == true)
             {
                 auto neighb_stub = neighbour_out_it->read();

                 auto neighb_key = neighbour_stub_outputs.get_key(*neighbour_out_it);
                 auto neighbour = neighb_key.second.Y_dim;
                 auto layer = neighb_key.second.X_dim;

                 log_buffer << sc_time_stamp() << " (N=" << neighbour << ",L=" << layer << "): ";
                 log_buffer << neighb_stub << std::endl;
             }

             ++neighbour_dv_it;
         }



    }

}
