
#include "module_test.hpp"

// *****************************************************************************
module_test::module_test(const sc_module_name _name, const sensor_module_config& configuration) :
        sc_module(_name),
        clock("clock"),
//        sensor_modules_test(2, "test_modules", configuration),
//        hit_fifos_test(2, 16, "hit_fifo_test"),
//        gbt_links_test(2, "gbt_test")

//        ctrls(10000, "ctrls"),
//        roads_detecteds(10000, "roads_detected"),
//        road_inputs(10000, "road_input"),
//        road_outputs(10000, "road_output")

        fe_chip_test(10000, "fe_chip_test", configuration.type->frontend_chip),
        stub_input(10000, "stub_in_test"),
        data_valid(10000, configuration.type->frontend_chip.max_stubs_per_cycle, "dv_test"),
        stub_outputs(10000, configuration.type->frontend_chip.max_stubs_per_cycle, "stub_out_test")

//       concentrators_test(10000, "test_concs", configuration.type->data_concentrator),
//       data_valid_test(10000, configuration.type->data_concentrator.fe_chips_count ,configuration.type->frontend_chip.max_stubs_per_cycle, "dv_test"),
//       fe_stub_in_test(10000, configuration.type->data_concentrator.fe_chips_count, configuration.type->frontend_chip.max_stubs_per_cycle, "stub_in_test"),
//       dc_out_test(10000, "dc_out_test")

//        gbt_unit_test(10000, "gbt_test", configuration.type->gbt),
//        gbt_in_test(10000, 2, "gbt_in_test"),
//        gbt_link_test(10000, "gbt_link_test")

{
    unsigned int i = 0;
//    for (sc_map_linear<sensor_module>::iterator module_it = sensor_modules_test.begin();
//         module_it != sensor_modules_test.end();
//         ++module_it)
//    {
//        module_it->clk.bind(clock);
//        module_it->stub_inputs.bind(hit_fifos_test(sc_map_square_key(i,0), sc_map_square_key(i, 16)));
//        module_it->gbt_link.bind(gbt_links_test[i]);
//
//        ++i;
//    }

//    i = 0;
//    for (sc_map_linear<am_chip_read_ctrl>::iterator ctrl_it = ctrls.begin();
//         ctrl_it != ctrls.end();
//         ++ctrl_it)
//    {
//        ctrl_it->clk.bind(clock);
//        ctrl_it->roads_detected.bind(roads_detecteds[i]);
//        ctrl_it->road_input.bind(road_inputs[i]);
//        ctrl_it->road_output.bind(road_outputs[i]);
//
//        ++i;
//    }

        i = 0;
        for (sc_map_linear<frontend_chip>::iterator fe_chip_it = fe_chip_test.begin();
                fe_chip_it != fe_chip_test.end();
                ++fe_chip_it)
        {
            fe_chip_it->clk.bind(clock);
            fe_chip_it->stub_input.bind(stub_input.at(i));
            fe_chip_it->data_valid.bind(data_valid(sc_map_square_key(i,0), sc_map_square_key(i, configuration.type->frontend_chip.max_stubs_per_cycle-1)));
            fe_chip_it->stub_outputs.bind(stub_outputs(sc_map_square_key(i,0), sc_map_square_key(i, configuration.type->frontend_chip.max_stubs_per_cycle-1)));

            ++i;
        }

//    i = 0;
//    for (sc_map_linear<data_concentrator>::iterator conc_it = concentrators_test.begin();
//            conc_it != concentrators_test.end();
//            ++conc_it)
//    {
//        conc_it->clk.bind(clock);
//        conc_it->data_valid.bind(data_valid_test(sc_map_cube_key(i,0,0),sc_map_cube_key(i,configuration.type->data_concentrator.fe_chips_count-1 ,configuration.type->frontend_chip.max_stubs_per_cycle-1)));
//        conc_it->fe_stub_in.bind(fe_stub_in_test(sc_map_cube_key(i,0,0),sc_map_cube_key(i,configuration.type->data_concentrator.fe_chips_count-1 ,configuration.type->frontend_chip.max_stubs_per_cycle-1)));
//        conc_it->dc_out.bind(dc_out_test.at(i));
//
//        ++i;
//    }

//    i = 0;
//    for (sc_map_linear<gbt>::iterator gbt_it = gbt_unit_test.begin();
//            gbt_it != gbt_unit_test.end();
//            ++gbt_it)
//    {
//        gbt_it->cic_in.bind(gbt_in_test(sc_map_square_key(i,0),sc_map_square_key(i,2)));
//        gbt_it->optical_link.bind(gbt_link_test.at(i));
//
//        ++i;
//    }

    return;
}
