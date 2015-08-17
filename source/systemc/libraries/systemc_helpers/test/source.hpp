
#pragma once

#include <systemc.h>

#include "../sc_map/include/sc_map.hpp"

class source : public sc_module
{
public:
    sc_map_linear<sc_out<bool> > output;

    void create_data();

    source(sc_module_name _name);
    SC_HAS_PROCESS(source);
};

class source_square : public sc_module
{
public:
    sc_map_square<sc_out<bool> > output;

    void create_data();

    source_square(sc_module_name _name);
    SC_HAS_PROCESS(source_square);
};

class source_cube : public sc_module
{
public:
    sc_map_cube<sc_out<bool> > output;

    void create_data();

    source_cube(sc_module_name _name);
    SC_HAS_PROCESS(source_cube);
};

class source_4d : public sc_module
{
public:
    sc_map_4d<sc_out<bool> > output;

    void create_data();

    source_4d(sc_module_name _name);
    SC_HAS_PROCESS(source_4d);
};
