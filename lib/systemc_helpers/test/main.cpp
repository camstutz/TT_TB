
#include <iostream>


#include <systemc.h>

#include "../sc_map/sc_map_linear.hpp"
#include "../sc_map/sc_map_square.hpp"
#include "../sc_map/sc_map_cube.hpp"
#include "../sc_map/sc_map_4d.hpp"
#include "../sc_analyzer/sc_analyzer.hpp"
#include "source.hpp"
#include "sink.hpp"



int sc_main(int argc, char *agv[])
{
    sc_analyzer myAnalyzer;

    myAnalyzer.register_model_setup_start();

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
    for (auto& this_sig : signals1)
    {
        std::pair<bool, sc_map_linear<sc_signal<bool> >::full_key_type> the_key = signals1.get_key(this_sig);
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

    // **** Setup Tracing
    sc_trace_file* fp;
    fp=sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, SC_NS);

    sc_trace(fp, signals1, "signal1");
    sc_trace(fp, signals2, "signal2");
    sc_trace(fp, signals3, "signal3");
    sc_trace(fp, signals4, "signal4");

    std::cout << "\n--- Simulation starts ---\n" << std::endl;

    myAnalyzer.register_model_setup_end();
    myAnalyzer.register_simulation_start();

    sc_start(1000, SC_NS);

    myAnalyzer.register_simulation_end();

    std::cout << "\n--- Simulation ended ---\n" << std::endl;

    sc_close_vcd_trace_file(fp);

    myAnalyzer.print_report();

    return(0);
}
