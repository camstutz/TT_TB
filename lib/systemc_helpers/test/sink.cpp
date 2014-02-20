
#include "sink.hpp"

//******************************************************************************
sink::sink(sc_module_name _name) :
        sc_module(_name),
        input(2, "in_port") {

    SC_THREAD(detect_signal);
        input.make_sensitive(this->sensitive);

    return;
}

//******************************************************************************
void sink::detect_signal()
{
    while (1) {
        wait();
        for (auto& in : input) {
            if (in.read() == true) {
                std::cout << sc_time_stamp() << " - " << in.name() << " = 1" << std::endl;
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
        input.make_sensitive(this->sensitive);

    return;
}

//******************************************************************************
void sink_square::detect_signal()
{
    while (1) {
        wait();
        for (auto& in : input) {
            if (in.read() == true) {
                std::cout << sc_time_stamp() << " - " << in.name() << " = 1" << std::endl;
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
        input.make_sensitive(this->sensitive);

    return;
}

//******************************************************************************
void sink_cube::detect_signal()
{
    while (1) {
        wait();
        for (auto& in : input) {
            if (in.read() == true) {
                std::cout << sc_time_stamp() << " - " << in.name() << " = 1" << std::endl;
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
        input.make_sensitive(this->sensitive);

    return;
}

//******************************************************************************
void sink_4d::detect_signal()
{
    while (1) {
        wait();
        for (auto& in : input) {
            if (in.read() == true) {
                std::cout << sc_time_stamp() << " - " << in.name() << " = 1" << std::endl;
            }
        }
    }

    return;
}
