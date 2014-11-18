/*!
 * @file road_processor.hpp
 * @author Christian Amstutz
 * @date Nov 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "am_ctrl_exp_config.hpp"

/*!
 * @brief
 */
class road_processor : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<road_t> road_input;
    sc_out<road_t> road_lookup;
    sc_map_linear<sc_in<superstrip_t> > found_pattern;
    sc_map_linear<sc_out<superstrip_t> > superstrip_lookup;
    sc_map_linear<sc_in<hit_t> > hit_lookup_result;
    sc_map_linear<sc_out<hit_t> > hit_output;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    road_processor(const sc_module_name _name);
    SC_HAS_PROCESS(road_processor);
};
