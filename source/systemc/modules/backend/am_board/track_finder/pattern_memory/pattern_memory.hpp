/*!
 * @file pattern_memory.hpp
 * @author Christian Amstutz
 * @date March 30, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include <map>

#include <systemc.h>

#include "../../../../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../pattern_bank/pattern_bank.hpp"
#include "../../../../../systems/TT_configuration.hpp"

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
    sc_map_linear<sc_signal<superstrip_t> > superstrip_outputs_sig;

    // ----- Process Declarations ----------------------------------------------
    void lookup_road();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_linear<sc_delay_signal<superstrip_t, PATTERN_MEMORY_LATENCY> > delay_superstrip_outputs;

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
