
#include <iostream>


#include <systemc.h>

#include "../sc_map/sc_map.hpp"
#include "../sc_analyzer/sc_analyzer.hpp"
#include "source.hpp"
#include "sink.hpp"
#include "bind_tester.hpp"

#include "sc_delay_tb.hpp"


int sc_main(int argc, char *agv[])
{
    //sc_analyzer myAnalyzer;

    //myAnalyzer.register_model_setup_start();

    source src1("source1");
    source_square src2("source2");
    source_cube src3("source3");
    source_4d src4("source4");

    sink snk1("sink1");
    sink_square snk2("sink2");
    sink_cube snk3("sink3");
    sink_4d snk4("sink4");

    sc_map_linear<sc_signal<bool> > signals1(2, "signal1");
    sc_map_square<sc_signal<bool> > signals2(3, 2, "signal2");
    sc_map_cube<sc_signal<bool> > signals3(4, 3, 2, "signal3");
    sc_map_4d<sc_signal<bool> > signals4(5, 4, 3, 2, "signal4");

    std::cout << "Signals in signals1: " << signals1.size() << std::endl;
    std::cout << "Signals in signals2: " << signals2.size() << " ("
              << signals2.size_Y() << "/"
              << signals2.size_X() << ")" << std::endl;
    std::cout << "Signals in signals3: " << signals3.size() << " ("
              << signals3.size_Z() << "/"
              << signals3.size_Y() << "/"
              << signals3.size_X() << ")" << std::endl;
    std::cout << "Signals in signals4: " << signals4.size() << " ("
              << signals4.size_W() << "/"
              << signals4.size_Z() << "/"
              << signals4.size_Y() << "/"
              << signals4.size_X() << ")" << std::endl;

    src1.output.bind(signals1);
    src2.output.bind(signals2);
    src3.output.bind(signals3);
    src4.output.bind(signals4);

    snk1.input.bind(signals1);
    snk2.input.bind(signals2);
    snk3.input.bind(signals3);
    snk4.input.bind(signals4);

    // Testing get_key()
    sc_map_linear<sc_signal<bool> >::iterator signal_it = signals1.begin();
    for (;signal_it != signals1.end(); ++signal_it)
    {
        std::pair<bool, sc_map_linear<sc_signal<bool> >::full_key_type> the_key = signals1.get_key(*signal_it);
        std::cout << "Key: " << the_key.first << " - " << the_key.second.X_dim << std::endl;
    }

    std::pair<bool, sc_map_linear<sc_signal<bool> >::full_key_type> the_key2 = signals1.get_key(signals1.at(0));
    std::cout << "Key: " << the_key2.first << " - " << the_key2.second.X_dim << std::endl;
    sc_signal<bool> test_signal;
    std::pair<bool, sc_map_linear<sc_signal<bool> >::full_key_type> the_key = signals1.get_key(test_signal);
    std::cout << "Key: " << the_key.first << " - " << the_key.second.X_dim << std::endl;

    std::pair<bool, sc_map_square<sc_signal<bool> >::full_key_type> the_key3 = signals2.get_key(signals2.at(1,1));
    std::cout << "Key: " << the_key3.first << " - " << the_key3.second.Y_dim << "," << the_key3.second.X_dim << std::endl;

    std::pair<bool, sc_map_cube<sc_signal<bool> >::full_key_type> the_key4 = signals3.get_key(signals3.at(3,1,1));
    std::cout << "Key: " << the_key4.first << " - " << the_key4.second.Z_dim << "," << the_key4.second.Y_dim << "," << the_key4.second.X_dim << std::endl;

    std::pair<bool, sc_map_4d<sc_signal<bool> >::full_key_type> the_key5 = signals4.get_key(signals4.at(2,3,0,1));
    std::cout << "Key: " << the_key5.first << " - " << the_key5.second.W_dim << ","<< the_key5.second.Z_dim << "," << the_key5.second.Y_dim << "," << the_key5.second.X_dim << std::endl;

    // Testing dimensional iterators
    sc_map_square<sc_signal<bool> > signals_sq(4, 3, "signalSQ");
    sc_map_iter_square<sc_signal<bool> > sig_iter = signals_sq.begin_partial(0, true, 1, true);
    sc_map_iter_sequential<sc_signal<bool> > end = signals_sq.end();
    std::cout << std::endl;
    for( ; sig_iter != end; ++sig_iter)
    {
        std::cout << (*sig_iter).name() << std::endl;
    }

    sc_map_iter_square<sc_signal<bool> > sig_iter2 = signals_sq.begin_partial(0, 1, true, 0, 1, true);
    std::cout << std::endl;
    for( ; sig_iter2 != end; ++sig_iter2)
    {
        std::cout << (*sig_iter2).name() << std::endl;
    }

    sc_map_iter_square<sc_signal<bool> > sig_iter3 = signals_sq.begin_partial(1, false, 1, true);
    std::cout << std::endl;
    for( ; sig_iter3 != end; ++sig_iter3)
    {
        std::cout << (*sig_iter3).name() << std::endl;
    }

    sc_map_cube<sc_out<bool> >::cube_iterator port_it3 = src3.output.begin_partial(2,true, 1,false, 1,false);
    sc_map_cube<sc_out<bool> >::iterator port_it3_end = src3.output.end();
    std::cout << std::endl;
    for( ; port_it3 != port_it3_end; ++port_it3)
    {
        std::cout << (*port_it3).name() << std::endl;
    }

    sc_map_iter_4d<sc_in<bool> > port_it4 = snk4.input.begin_partial(3,false, 1,false, 1,true, 1,false);
    sc_map_iter_sequential<sc_in<bool> > port_it4_end = snk4.input.end();
    std::cout << std::endl;
    for( ; port_it4 != port_it4_end; ++port_it4)
    {
        std::cout << (*port_it4).name() << std::endl;
    }
    std::cout << std::endl;

    // Test multi-dimensional partial binding
    sc_map_linear<sc_signal<bool> > bind_signals(10, "bsigs");
    bind_tester btest1("btest1");
//    auto iter2 = bind_signals.begin();
//    bool result = btest1.output.bind(0,2,false, 0,1,true, iter2);
//    std::cout << "result of binding: " << result << std::endl;
//    ++iter2;
//    result = btest1.output.bind(1,2,false, 0,1,true, iter2);
//    std::cout << "result of binding: " << result << std::endl;
//    ++iter2;
//    result = btest1.output.bind(2,2,false, 0,1,true, iter2);
//    std::cout << "result of binding: " << result << std::endl;

    //bind_signals.write_all(true);

    sc_map_square<sc_out<bool> >::square_iterator p_iter = btest1.output.begin_partial(0,1,true, 0,1,true);
    sc_map_linear<sc_signal<bool> >::iterator s_iter = bind_signals.begin();
    btest1.output.bind_by_iter(p_iter, s_iter);

    btest1.output.at(2,0).bind(bind_signals.at(8));
    btest1.output.at(2,1).bind(bind_signals.at(7));

    // **** Setup Tracing
    sc_trace_file* fp;
    fp=sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, SC_NS);

//    sc_trace(fp, signals1, "signal1");
//    sc_trace(fp, signals2, "signal2");
//    sc_trace(fp, signals3, "signal3");
//    sc_trace(fp, signals4, "signal4");
//    sc_trace(fp, bind_signals, "b_signal");

    sc_delay_tb delay_testbench("delay_testbench");
    sc_trace(fp, delay_testbench.clock, "clock");
    sc_trace(fp, delay_testbench.in_signal, "in");
    sc_trace(fp, delay_testbench.out_signal, "delayed");
    sc_trace(fp, delay_testbench.delay_element.read_ptr, "read_ptr");
    sc_trace(fp, delay_testbench.delay_element.write_ptr, "write_ptr");
    sc_trace(fp, delay_testbench.delay_element.signal_received, "received");

    std::cout << "\n--- Simulation starts ---\n" << std::endl;

    //myAnalyzer.register_model_setup_end();
    //myAnalyzer.register_simulation_start();

    sc_start(1000, SC_NS);

    //myAnalyzer.register_simulation_end();

    std::cout << "\n--- Simulation ended ---\n" << std::endl;

    sc_close_vcd_trace_file(fp);

    //myAnalyzer.print_report();

    return(0);
}
