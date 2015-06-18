
#include <systemc.h>

#include "../sc_map/sc_map.hpp"

class sink : public sc_module {
public:
    sc_map_linear<sc_in<bool> > input;

    void detect_signal();

    sink(sc_module_name _name);
    SC_HAS_PROCESS(sink);
};

class sink_square : public sc_module {
public:
    sc_map_square<sc_in<bool> > input;

    void detect_signal();

    sink_square(sc_module_name _name);
    SC_HAS_PROCESS(sink_square);
};

class sink_cube : public sc_module {
public:
    sc_map_cube<sc_in<bool> > input;

    void detect_signal();

    sink_cube(sc_module_name _name);
    SC_HAS_PROCESS(sink_cube);
};

class sink_4d : public sc_module {
public:
    sc_map_4d<sc_in<bool> > input;

    void detect_signal();

    sink_4d(sc_module_name _name);
    SC_HAS_PROCESS(sink_4d);
};

class sink_config
{
public:
    unsigned int config_value;
};

class sink_configurable : public sc_module {
public:
    sc_in<bool> input;
    unsigned int config_value;

    void detect_signal_config();

    sink_configurable(sc_module_name _name);
    sink_configurable(sc_module_name _name, sink_config configuration);
    SC_HAS_PROCESS(sink_configurable);
};
