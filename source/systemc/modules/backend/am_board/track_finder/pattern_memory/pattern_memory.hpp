/*!
 * @file pattern_memory.hpp
 * @author Christian Amstutz
 * @date February 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include <map>

#include <systemc.h>
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../pattern_bank/pattern_bank.hpp"
#include "../track_finder_config.hpp"

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
    void lookup_road();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    pattern_memory(const sc_module_name _name, pattern_bank *p_bank);
    SC_HAS_PROCESS(pattern_memory);

private:
    void print_pattern_bank();

    pattern_bank *patterns;
};
