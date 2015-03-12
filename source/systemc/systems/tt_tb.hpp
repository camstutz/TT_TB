/*!
 * @file tt_tb.hpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include <utility>

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../data_formats/fm_out_data.hpp"

#include "TT_configuration.hpp"
#include "../modules/LHC_cycle_counter/LHC_cycle_counter.hpp"
#include "../modules/hit_generator/hit_generator.hpp"
#include "../modules/frontend_cbc/sensor_module_cbc.hpp"
#include "../modules/frontend_mpa/sensor_module_mpa.hpp"
#include "../modules/backend/trigger_tower.hpp"
#include "../modules/road_analyzer/road_analyzer.hpp"

/*!
 * @brief
 */
class tt_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_clock LHC_clock;
    sc_clock LHCx4_clock;
    sc_clock AM_clock;
    sc_signal<bool> true_sig;
    sc_map_4d<sc_fifo<hit_generator::mpa_stub_t> > hit_fifos_mpa;
    sc_map_4d<sc_fifo<hit_generator::cbc_stub_t> > hit_fifos_cbc;
    sc_map_cube<sc_signal<sensor_module_cbc::dc_out_t> > fe_signals;

    sc_map_cube<sc_buffer<track_finder::hit_stream> > result_hits;

    sc_signal<unsigned int> hit_cnt_sig;

    sc_map_cube<sc_signal<bool> > neighbour_dv_sig;
    sc_map_cube<sc_signal<do_stub_t> > neighbour_stub_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    LHC_cycle_counter LHC_cycle_cnt;
    hit_generator hitGenerator;
    sc_map_cube<sensor_module_mpa> sensor_modules_mpa;
    sc_map_cube<sensor_module_cbc> sensor_modules_cbc;
    trigger_tower trigger_tower_0_0;
    trigger_tower trigger_tower_0_1;
    trigger_tower trigger_tower_1_0;
    trigger_tower trigger_tower_1_1;
    road_analyzer roadAnalyzer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    tt_tb(const sc_module_name _name);
    SC_HAS_PROCESS(tt_tb);
};
