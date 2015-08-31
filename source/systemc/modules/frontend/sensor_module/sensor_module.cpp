/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date August 25, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sensor_module.hpp"

// *****************************************************************************
sensor_module::sensor_module(
        const sc_module_name _name, const sensor_module_config& configuration) :
        sc_module(_name),
        configuration(configuration),
        sides(configuration.type.side_count),
        fe_chips_per_side(configuration.type.fe_chip_per_side),
        hits_per_fe_chip(configuration.type.frontend_chip.max_stubs_per_cycle),
        clk("clk"),
        stub_inputs(sides, fe_chips_per_side, "stub_inputs"),
        gbt_link("gbt_link"),
        fe_data_valid_signals(sides, fe_chips_per_side, hits_per_fe_chip, "fe_data_valid_sig"),
        fe_out_signals(sides, fe_chips_per_side, hits_per_fe_chip, "fe_out_sig"),
        cic_out_signals(configuration.type.side_count, "cic_out_signals"),
        front_end_chips(configuration.type.side_count, configuration.type.fe_chip_per_side, "front_end_chip", configuration.type.frontend_chip),
        concentrators(configuration.type.side_count, "CICs", configuration.type.data_concentrator),
        gbt_unit("GBT_unit", configuration.type.gbt)
{
    // ----- Module / Port / Signal - creation and naming ----------------------

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    for (unsigned int side = 0; side < sides; ++side)
    {
        for (unsigned int fe_chip_nr = 0; fe_chip_nr < fe_chips_per_side; ++fe_chip_nr)
        {
            frontend_chip& fe_chip = front_end_chips.at(side, fe_chip_nr);
            fe_chip.clk.bind(clk);
            fe_chip.stub_input.bind(stub_inputs.at(side, fe_chip_nr));
            fe_chip.data_valid.bind(fe_data_valid_signals(sc_map_cube_key(side, fe_chip_nr, 0), sc_map_cube_key(side, fe_chip_nr, hits_per_fe_chip)));
            fe_chip.stub_outputs.bind(fe_out_signals(sc_map_cube_key(side, fe_chip_nr, 0), sc_map_cube_key(side, fe_chip_nr, hits_per_fe_chip)));
        }
    }

    unsigned int side_selector = 0;
    typename sc_map_linear<data_concentrator>::iterator cic_it = concentrators.begin();
    for (; cic_it != concentrators.end(); ++cic_it)
    {
        cic_it->clk.bind(clk);
        cic_it->data_valid.bind(fe_data_valid_signals(sc_map_cube_key(side_selector, 0, 0), sc_map_cube_key(side_selector, fe_chips_per_side-1, hits_per_fe_chip-1)));
        cic_it->fe_stub_in.bind(fe_out_signals(sc_map_cube_key(side_selector, 0, 0), sc_map_cube_key(side_selector, fe_chips_per_side-1, hits_per_fe_chip-1)));
        cic_it->dc_out.bind(cic_out_signals[side_selector]);

        ++side_selector;
    }

    gbt_unit.cic_in.bind(cic_out_signals);
    gbt_unit.optical_link.bind(gbt_link);

#ifdef MTI_SYSTEMC
    // stub_inputs.register_signal_modelsim<fe_out_data::fe_stub_t>();
    // fe_out_signals.register_signal_modelsim<fe_out_data>();
#endif

    return;
}
