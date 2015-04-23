/*!
 * @file sensor_module.hpp
 * @author Christian Amstutz
 * @date April 23, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "frontend_chip.hpp"
#include "data_concentrator.hpp"
#include "gbt.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

// *****************************************************************************
/*!
 * @brief SystemC module which represents one sensor module of the detector.
 * Combines the front end chips and the data concentrator.
 */

template <typename FE_CHIP_TYPE, typename CIC_TYPE, unsigned int HITS_PER_CYCLE>
class sensor_module : public sc_module
{
public:

    typedef FE_CHIP_TYPE fe_chip_t;
    typedef CIC_TYPE cic_t;
    typedef typename fe_chip_t::input_stub_t fe_stub_t;
    typedef typename cic_t::output_t cic_out_t;
    typedef typename gbt::output_t gbt_link_t;

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
    gbt gbt_unit;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    sensor_module(const sc_module_name _name);
};
// *****************************************************************************

typedef sensor_module<frontend_chip_cbc, data_concentrator_cbc, MAX_HITS_PER_CBC_FE_CHIP> sensor_module_CBC;

typedef sensor_module<frontend_chip_mpa, data_concentrator_mpa, MAX_HITS_PER_MPA_FE_CHIP> sensor_module_MPA;

// *****************************************************************************

// *****************************************************************************

template <typename FE_CHIP_TYPE, typename CIC_TYPE, unsigned int HITS_PER_CYCLE>
const unsigned int sensor_module<FE_CHIP_TYPE, CIC_TYPE, HITS_PER_CYCLE>::sides = NR_FE_CHIP_SIDES;

template <typename FE_CHIP_TYPE, typename CIC_TYPE, unsigned int HITS_PER_CYCLE>
const unsigned int sensor_module<FE_CHIP_TYPE, CIC_TYPE, HITS_PER_CYCLE>::fe_chips_per_side = NR_FE_CHIP_PER_SIDE;

template <typename FE_CHIP_TYPE, typename CIC_TYPE, unsigned int HITS_PER_CYCLE>
const unsigned int sensor_module<FE_CHIP_TYPE, CIC_TYPE, HITS_PER_CYCLE>::hits_per_fe_chip = HITS_PER_CYCLE;

// *****************************************************************************
template <typename FE_CHIP_TYPE, typename CIC_TYPE, unsigned int HITS_PER_CYCLE>
sensor_module<FE_CHIP_TYPE, CIC_TYPE, HITS_PER_CYCLE>::sensor_module(
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
        gbt_unit("GBT_unit")
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
            fe_chip.clk.bind(clk);
            fe_chip.stub_input.bind(stub_inputs.at(side, fe_chip_nr));
            typename sc_map_cube<sc_signal<bool> >::cube_iterator data_valid_sig_it = fe_data_valid_signals.begin_partial(side, false, fe_chip_nr, false, 0, true);
            fe_chip.data_valid.bind_by_iter(data_valid_sig_it);
            typename sc_map_cube<sc_signal<fe_stub_t> >::cube_iterator fe_out_sig_it = fe_out_signals.begin_partial(side, false, fe_chip_nr, false, 0, true);
            fe_chip.stub_outputs.bind_by_iter(fe_out_sig_it);
        }
    }

    unsigned int side_selector = 0;
    typename sc_map_linear<cic_t>::iterator cic_it = concentrators.begin();
    for (; cic_it != concentrators.end(); ++cic_it)
    {
        cic_it->clk.bind(clk);
        typename sc_map_cube<sc_signal<bool> >::cube_iterator data_valid_sig_it = fe_data_valid_signals.begin_partial(side_selector, false, 0, true, 0, true);
        cic_it->data_valid.bind_by_iter(data_valid_sig_it);
        typename sc_map_cube<sc_signal<fe_stub_t> >::cube_iterator fe_out_sig_it = fe_out_signals.begin_partial(side_selector, false, 0, true, 0, true);
        cic_it->fe_stub_in.bind_by_iter(fe_out_sig_it);
        cic_it->dc_out.bind(cic_out_signals[side_selector]);

        ++side_selector;
    }

    gbt_unit.clk.bind(clk);
    gbt_unit.cic_in.bind(cic_out_signals);
    gbt_unit.optical_link.bind(gbt_link);

#ifdef MTI_SYSTEMC
    // stub_inputs.register_signal_modelsim<fe_out_data::fe_stub_t>();
    // fe_out_signals.register_signal_modelsim<fe_out_data>();
#endif

    return;
}
