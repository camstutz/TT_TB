/*!
 * @file pattern_memory.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "../../../../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../pattern_bank/pattern_bank.hpp"

#include "../../../../../systems/TT_configuration.hpp"
#include "pattern_memory_config.hpp"

#include <systemc.h>

#include <map>

/*!
 * @brief
 */
class pattern_memory : public sc_module
{
public:
    const unsigned int layer_nr;

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
    pattern_memory(const sc_module_name _name, const pattern_memory_config configuration);
    SC_HAS_PROCESS(pattern_memory);

    void link_pattern_bank(pattern_bank* bank);

private:
    void print_pattern_bank();

    pattern_bank *patterns;
};
