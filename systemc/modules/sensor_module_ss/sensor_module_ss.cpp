/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date May 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "sensor_module_ss.hpp"

// *****************************************************************************

/*!
 * @class sensor_module
 */

sensor_module_ss::sensor_module_ss(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        stub_inputs(NR_FE_CHIP_PER_MODULE, "stub_in", 0),
        dc_out("dc_out"),
        fe_out_signals(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_FE_CHIP,
                "fe_out_sig", 0, 0),
        true_sig("true"),
        front_end_chips(NR_FE_CHIP_PER_MODULE, "front_end_chip", 0),
        dataConcentrator("DC")
{
    // ----- Module / Port / Signal - creation and naming ----------------------

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    unsigned int fe_cnt = 0;
    sc_map_linear<front_end_chip>::iterator fe_chip_it = front_end_chips.begin();
    for (; fe_chip_it != front_end_chips.end(); ++fe_chip_it)
    {
        fe_chip_it->clk.bind(clk);
        //! todo: use the enable port
        fe_chip_it->en(true_sig);
        fe_chip_it->stub_input(stub_inputs[fe_cnt]);
        sc_map_square<sc_signal<fe_out_data> >::square_iterator fe_out_sig_it = fe_out_signals.begin_partial(fe_cnt, false, 0, true);
        fe_chip_it->hit_outputs.bind_by_iter(fe_out_sig_it);

        fe_cnt++;
    }

    dataConcentrator.clk(clk);
    dataConcentrator.rst(true_sig);
    dataConcentrator.fe_stub_in.bind(fe_out_signals);
    dataConcentrator.dc_out(dc_out);

#ifdef MODELSIM_COMPILER
    stub_inputs.register_signal_modelsim<fe_out_data::fe_stub_t>();
    fe_out_signals.register_signal_modelsim<fe_out_data>();
#endif

    true_sig.write(true);

    return;
}
