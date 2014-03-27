/*!
 * @file data_concentrator_tb.hpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iostream>
#include <sstream>

#include "systemc.h"

#include "../lib/systemc_helpers/sc_map/sc_map_square.hpp"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/data_concentrator.hpp"
#include "../systemc/data_representations/fe_out_data.hpp"

/*!
 * @brief
 */
class data_concentrator_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> rst;
    sc_map_square<sc_signal<fe_out_data> > fe_signals;
    sc_signal<sc_bv<DC_OUTPUT_WIDTH> > dc_output;

    // ----- Process Declarations ----------------------------------------------
    void generate_hit_data();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------
    void write_fe(const unsigned int fe_chip, const unsigned int hit_nr,
            const unsigned int address, const unsigned int bend);
    void release_fe(const unsigned int fe_chip, const unsigned int hit_nr);

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    data_concentrator dut_data_concentrator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    data_concentrator_tb(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator_tb);
    ~data_concentrator_tb();
    void end_of_elaboration();

private:
    std::ostringstream log_buffer;
};
