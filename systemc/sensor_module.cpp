/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date Mar 12, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "sensor_module.hpp"

// *****************************************************************************

/*!
 * @class sensor_module
 *
 * The module is sensitive to ....
 */

sensor_module::sensor_module(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        stub_inputs(NR_FE_CHIP_PER_MODULE, "stub_in", 1),
        dc_out("dc_out"),
        fe_out_signals(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_FE_CHIP, "fe_out_sig", 1, 1),
        true_sig("true"),
        front_end_chips(NR_FE_CHIP_PER_MODULE, "front_end_chip", 1),
        dataConcentrator("DC")
{
    // ----- Module / Port / Signal - creation and naming ------------------------

    // ----- Process registration ------------------------------------------------

    // ----- Module variable initialization --------------------------------------

    // ----- Module instance / channel binding -----------------------------------

    unsigned int fe_cnt = 1;
    for (auto& fe_chip: front_end_chips) {
        fe_chip.clk(clk);
        //! todo: use the enable port
        fe_chip.en(true_sig);
        fe_chip.stub_input(stub_inputs[fe_cnt]);
        auto fe_out_sig_it = fe_out_signals.begin_partial(fe_cnt, false, 0, true);
        fe_chip.hit_outputs.bind_by_iter(fe_out_sig_it);

        fe_cnt++;
    }

    dataConcentrator.clk(clk);
    dataConcentrator.rst(true_sig);
    dataConcentrator.fe_stub_in.bind(fe_out_signals);
    dataConcentrator.dc_out(dc_out);

    true_sig.write(true);

    return;
}
