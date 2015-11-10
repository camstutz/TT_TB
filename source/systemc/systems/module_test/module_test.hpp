#pragma once

#include "../../modules/frontend/sensor_module/sensor_module.hpp"
#include "../../modules/frontend/frontend_chip/frontend_chip.hpp"
#include "../../modules/backend/am_board/track_finder/am_chip/am_chip_read_ctrl.hpp"


#include "sc_map.hpp"

#include <systemc.h>

class module_test : public sc_module
{
public:
    sc_in<bool> clock;

//    sc_map_linear<sensor_module> sensor_modules_test;
//    sc_map_square<sc_fifo<stub> > hit_fifos_test;
//    sc_map_linear<sc_buffer<gbt_link_format> > gbt_links_test;

//    sc_map_linear<am_chip_read_ctrl> ctrls;
//    sc_map_linear<sc_signal<bool> > roads_detecteds;
//    sc_map_linear<sc_fifo<road_t> > road_inputs;
//    sc_map_linear<sc_signal<am_chip_read_ctrl::road_stream> > road_outputs;

    sc_map_linear<frontend_chip> fe_chip_test;
    sc_map_linear<sc_fifo<stub> > stub_input;
    sc_map_square<sc_signal<bool> > data_valid;
    sc_map_square<sc_signal<stub> > stub_outputs;

//    sc_map_linear<data_concentrator> concentrators_test;
//    sc_map_cube<sc_signal<bool> > data_valid_test;
//    sc_map_cube<sc_signal<data_concentrator::fe_stub_t> > fe_stub_in_test;
//    sc_map_linear<sc_signal<data_concentrator::output_t> > dc_out_test;

//    sc_map_linear<gbt> gbt_unit_test;
//    sc_map_square<sc_buffer<sensor_module::cic_out_t> > gbt_in_test;
//    sc_map_linear<sc_signal<sensor_module::gbt_link_t> > gbt_link_test;

    module_test(const sc_module_name _name, const sensor_module_config& test_module_configs);
};
