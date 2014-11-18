/*!
 * @file pattern_memory.hpp
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
class pattern_memory : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<road_t> road_input;
    sc_map_linear<sc_out<superstrip_t> > superstrip_outputs;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    pattern_memory(const sc_module_name _name);
    SC_HAS_PROCESS(pattern_memory);
};
