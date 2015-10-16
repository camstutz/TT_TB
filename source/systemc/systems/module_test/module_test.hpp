#pragma once

#include "../../modules/frontend/sensor_module/sensor_module.hpp"

#include "sc_map.hpp"

#include <systemc.h>

class module_test : public sc_module
{
public:
    sc_in<bool> clock;
    sc_map_linear<sensor_module> sensor_modules_test;
    sc_map_linear<sc_fifo<stub> > hit_fifos_test;
    sc_map_linear<sc_buffer<gbt_link_format> > gbt_links_test;

    module_test(const sc_module_name _name, const std::vector<sensor_module_config>& test_module_configs);
};
