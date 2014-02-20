
#include <systemc.h>

#include "../sc_map/sc_map_linear.hpp"
#include "../sc_map/sc_map_square.hpp"
#include "../sc_map/sc_map_cube.hpp"
#include "../sc_map/sc_map_4d.hpp"

class sink : public sc_module {
public:
    sc_map_linear<sc_in<bool>> input;

    void detect_signal();

    sink(sc_module_name _name);
    SC_HAS_PROCESS(sink);
};

class sink_square : public sc_module {
public:
    sc_map_square<sc_in<bool>> input;

    void detect_signal();

    sink_square(sc_module_name _name);
    SC_HAS_PROCESS(sink_square);
};

class sink_cube : public sc_module {
public:
    sc_map_cube<sc_in<bool>> input;

    void detect_signal();

    sink_cube(sc_module_name _name);
    SC_HAS_PROCESS(sink_cube);
};

class sink_4d : public sc_module {
public:
    sc_map_4d<sc_in<bool>> input;

    void detect_signal();

    sink_4d(sc_module_name _name);
    SC_HAS_PROCESS(sink_4d);
};
