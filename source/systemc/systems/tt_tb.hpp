/*!
 * @file tt_tb.hpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "../modules/hit_generator/hit_generator.hpp"
#include "../modules/frontend/sensor_module.hpp"
#include "../modules/backend/dtc/dtc.hpp"
#include "../modules/backend/trigger_tower.hpp"
#include "../modules/road_analyzer/road_analyzer.hpp"

#include "../data_formats/stub.hpp"

#include "TT_configuration.hpp"
#include "../TT_configuration/track_trigger_config.hpp"

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

#include <utility>

// *****************************************************************************
/*!
 * @brief
 */
class tt_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_clock LHC_clock;
    sc_signal<bool> true_sig;
    sc_map_4d<sc_fifo<stub> > hit_fifos;
    sc_map_cube<sc_buffer<gbt_link_format> > gbt_links;
    sc_map_linear<sc_buffer<dtc::output_t> > dtc_links;
    sc_map_square<sc_buffer<track_finder::hit_stream> > result_hits;

    sc_signal<unsigned int> hit_cnt_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    hit_generator hitGenerator;
    sc_map_cube<sensor_module> sensor_modules_mpa;
    sc_map_cube<sensor_module> sensor_modules_cbc;
    sc_map_linear<dtc> DTCs;
    trigger_tower trigger_tower_0;
    road_analyzer roadAnalyzer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    tt_tb(const sc_module_name _name, const track_trigger_config configuration);
    SC_HAS_PROCESS(tt_tb);
};
