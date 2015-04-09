/*!
 * @file sensor_module.hpp
 * @author Christian Amstutz
 * @date April 9, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"

/*!
 * @brief SystemC module which represents one sensor module of the detector.
 * Combines the front end chips and the data concentrator.
 */

template <typename FE_CHIP_TYPE, typename CIC_TYPE, typename GBT_TYPE,
        unsigned int NR_FE_CHIPS, unsigned int HITS_PER_CYCLE>
class sensor_module : public sc_module
{
public:

    typedef FE_CHIP_TYPE fe_chip_t;
    typedef CIC_TYPE cic_t;
    typedef GBT_TYPE gbt_t;
    typedef typename fe_chip_t::input_stub_t fe_stub_t;
    typedef typename cic_t::output_t cic_out_t;
    typedef typename gbt_t::output_t gbt_link_t;

    static const unsigned int sides;
    static const unsigned int fe_chips_per_side;
    static const unsigned int hits_per_fe_chip;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_square<sc_fifo_in<fe_stub_t> > stub_inputs;
    sc_out<gbt_link_t> gbt_link;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_cube<sc_signal<bool> > fe_data_valid_signals;
    sc_map_cube<sc_signal<fe_stub_t> > fe_out_signals;
    sc_map_linear<sc_buffer<cic_out_t> > cic_out_signals;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_square<fe_chip_t> front_end_chips;
    sc_map_linear<cic_t> concentrators;
    gbt_t gbt;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    sensor_module(const sc_module_name _name);
};


// *****************************************************************************

// *****************************************************************************

template <typename FE_CHIP_TYPE, typename CIC_TYPE, typename GBT_TYPE,
        unsigned int NR_FE_CHIPS, unsigned int HITS_PER_CYCLE>
const unsigned int sensor_module<FE_CHIP_TYPE, CIC_TYPE, GBT_TYPE, NR_FE_CHIPS, HITS_PER_CYCLE>::sides = 2;

template <typename FE_CHIP_TYPE, typename CIC_TYPE, typename GBT_TYPE,
        unsigned int NR_FE_CHIPS, unsigned int HITS_PER_CYCLE>
const unsigned int sensor_module<FE_CHIP_TYPE, CIC_TYPE, GBT_TYPE, NR_FE_CHIPS, HITS_PER_CYCLE>::fe_chips_per_side = NR_FE_CHIPS;

template <typename FE_CHIP_TYPE, typename CIC_TYPE, typename GBT_TYPE,
        unsigned int NR_FE_CHIPS, unsigned int HITS_PER_CYCLE>
const unsigned int sensor_module<FE_CHIP_TYPE, CIC_TYPE, GBT_TYPE, NR_FE_CHIPS, HITS_PER_CYCLE>::hits_per_fe_chip = HITS_PER_CYCLE;

// *****************************************************************************
template <typename FE_CHIP_TYPE, typename CIC_TYPE, typename GBT_TYPE,
        unsigned int NR_FE_CHIPS, unsigned int HITS_PER_CYCLE>
sensor_module<FE_CHIP_TYPE, CIC_TYPE, GBT_TYPE, NR_FE_CHIPS, HITS_PER_CYCLE>::sensor_module(
        const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        stub_inputs(sides, fe_chips_per_side, "stub_inputs", 0),
        gbt_link("gbt_link"),
        fe_data_valid_signals(sides, fe_chips_per_side, hits_per_fe_chip, "fe_data_valid_sig", 0, 0),
        fe_out_signals(sides, fe_chips_per_side, hits_per_fe_chip, "fe_out_sig", 0, 0),
        cic_out_signals(sides, "cic_out_signals", 0),
        front_end_chips(sides, fe_chips_per_side, "front_end_chip", 0),
        concentrators(sides, "CICs"),
        gbt("GBT")
{
    // ----- Module / Port / Signal - creation and naming ----------------------

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    for (unsigned int side = 0; side < sides; ++side)
    {
        for (unsigned int fe_chip_nr = 0; fe_chip_nr < fe_chips_per_side; ++fe_chip_nr)
        {
            fe_chip_t& fe_chip = front_end_chips.at(side, fe_chip_nr);
            fe_chip.bind.clk(clk);
            fe_chip.bind.stub_input(stub_inputs.at(side, fe_chip_nr));
            typename sc_map_square<sc_signal<bool> >::square_iterator data_valid_sig_it = fe_data_valid_signals.begin_partial(side, false, fe_chip_nr, false, 0, true);
            fe_chip.stub_outputs.bind_by_iter(data_valid_sig_it);
            typename sc_map_square<sc_signal<fe_stub_t> >::square_iterator fe_out_sig_it = fe_out_signals.begin_partial(side, false, fe_chip_nr, false, 0, true);
            fe_chip.stub_outputs.bind_by_iter(fe_out_sig_it);
        }
    }

    unsigned int side_selector = 0;
    typename sc_map_linear<cic_t>::iterator cic_it = concentrators.begin();
    for (; cic_it != concentrators.end(); ++cic_it)
    {
        cic_it->clk.bind(clk);
        cic_it->data_valid.bind();
        cic_it->fe_stub_in.bind();
        cic_it->dc_out.bind(cic_out_signals);
    }

    gbt.clk.bind(clk);
    gbt.cic_in.bind(cic_out_signals);
    gbt.optical_link.bind(gbt_link);

#ifdef MTI_SYSTEMC
    // stub_inputs.register_signal_modelsim<fe_out_data::fe_stub_t>();
    // fe_out_signals.register_signal_modelsim<fe_out_data>();
#endif

    return;
}
