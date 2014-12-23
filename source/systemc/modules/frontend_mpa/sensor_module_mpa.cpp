/*!
 * @file sensor_module_mpa.cpp
 * @author Christian Amstutz
 * @date December 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "sensor_module_mpa.hpp"

// *****************************************************************************

/*!
 * @class sensor_module
 */

sensor_module_mpa::sensor_module_mpa(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        stub_inputs(NR_FE_CHIP_PER_MODULE, "stub_in", 0),
        dc_out("dc_out"),
        data_valid_signals(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_MPA_FE_CHIP,
                "data_valid_sig", 0, 0),
        fe_out_signals(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_MPA_FE_CHIP,
                "fe_out_sig", 0, 0),
        front_end_chips(NR_FE_CHIP_PER_MODULE, "front_end_chip", 0),
        dataConcentrator("data_concentrator")
{
    // ----- Module / Port / Signal - creation and naming ----------------------

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    unsigned int fe_cnt = 0;
    sc_map_linear<frontend_chip_mpa>::iterator fe_chip_it = front_end_chips.begin();
    for (; fe_chip_it != front_end_chips.end(); ++fe_chip_it)
    {
        fe_chip_it->clk.bind(clk);
        fe_chip_it->stub_input(stub_inputs[fe_cnt]);
        sc_map_square<sc_signal<bool> >::square_iterator data_valid_sig_it = data_valid_signals.begin_partial(fe_cnt, false, 0, true);
        fe_chip_it->data_valid.bind_by_iter(data_valid_sig_it);
        sc_map_square<sc_signal<fe_stub_t> >::square_iterator fe_out_sig_it = fe_out_signals.begin_partial(fe_cnt, false, 0, true);
        fe_chip_it->stub_outputs.bind_by_iter(fe_out_sig_it);

        fe_cnt++;
    }

    dataConcentrator.clk.bind(clk);
    dataConcentrator.data_valid.bind(data_valid_signals);
    dataConcentrator.fe_stub_in.bind(fe_out_signals);
    dataConcentrator.dc_out.bind(dc_out);

#ifdef MTI_SYSTEMC
    stub_inputs.register_signal_modelsim<fe_out_data::fe_stub_t>();
    fe_out_signals.register_signal_modelsim<fe_out_data>();
#endif

    return;
}
