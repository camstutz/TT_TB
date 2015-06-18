
#include "sink.hpp"

//******************************************************************************
sink::sink(sc_module_name _name) :
        sc_module(_name),
        input(2, "in_port") {

    SC_THREAD(detect_signal);
        sensitive << input;

    return;
}

//******************************************************************************
void sink::detect_signal()
{
    while (1) {
        wait();
        sc_map_linear<sc_in<bool> >::iterator in_it = input.begin();
        for (; in_it != input.end(); ++in_it)
        {
            if (in_it->read() == true) {
                std::cout << sc_time_stamp() << " - " << in_it->name() << " = 1" << std::endl;
            }
        }
    }

    return;
}

//******************************************************************************
sink_square::sink_square(sc_module_name _name) :
        sc_module(_name),
        input(3, 2, "in_port") {

    SC_THREAD(detect_signal);
        sensitive << input;

    return;
}

//******************************************************************************
void sink_square::detect_signal()
{
    while (1) {
        wait();
        sc_map_square<sc_in<bool> >::iterator in_it = input.begin();
        for (; in_it != input.end(); ++in_it)
        {
            if (in_it->read() == true) {
                std::cout << sc_time_stamp() << " - " << in_it->name() << " = 1" << std::endl;
            }
        }
    }

    return;
}

//******************************************************************************
sink_cube::sink_cube(sc_module_name _name) :
        sc_module(_name),
        input(4, 3, 2, "in_port") {

    SC_THREAD(detect_signal);
        sensitive << input;

    return;
}

//******************************************************************************
void sink_cube::detect_signal()
{
    while (1) {
        wait();
        sc_map_cube<sc_in<bool> >::iterator in_it = input.begin();
        for (; in_it != input.end(); ++in_it)
        {
            if (in_it->read() == true)
            {
                std::cout << sc_time_stamp() << " - " << in_it->name() << " = 1" << std::endl;
            }
        }
    }

    return;
}

//******************************************************************************
sink_4d::sink_4d(sc_module_name _name) :
        sc_module(_name),
        input(5, 4, 3, 2, "in_port") {

    SC_THREAD(detect_signal);
        sensitive << input;

    return;
}

//******************************************************************************
void sink_4d::detect_signal()
{
    while (1) {
        wait();
        sc_map_4d<sc_in<bool> >::iterator in_it = input.begin();
        for (; in_it != input.end(); ++in_it)
        {
            if (in_it->read() == true)
            {
                std::cout << sc_time_stamp() << " - " << in_it->name() << " = 1" << std::endl;
            }
        }
    }

    return;
}

//******************************************************************************
sink_configurable::sink_configurable(sc_module_name _name) :
        sc_module(_name),
        input("input")
{
    config_value = 8;

    SC_THREAD(detect_signal_config);
        sensitive << input;

    return;
}

//******************************************************************************
sink_configurable::sink_configurable(sc_module_name _name, sink_config configuration) :
        sc_module(_name),
        input("input")
{
    config_value = configuration.config_value;

    SC_THREAD(detect_signal_config);
        sensitive << input;

    return;
}

//******************************************************************************
void sink_configurable::detect_signal_config()
{
    while (1)
    {
        wait();

        std::cout << sc_time_stamp() << " {" << config_value << "}" << " - " << input.name() << " = 1" << std::endl;
    }

    return;
}
