
#pragma once

#include <systemc.h>

#include "../sc_map/sc_map_linear.hpp"
#include "../sc_map/sc_map_square.hpp"
#include "../sc_map/sc_map_cube.hpp"
#include "../sc_map/sc_map_4d.hpp"

class bind_tester : public sc_module
{
public:
    sc_map_square<sc_out<bool> > output;

    void create_data();

    bind_tester(sc_module_name _name);
    SC_HAS_PROCESS(bind_tester);
};
