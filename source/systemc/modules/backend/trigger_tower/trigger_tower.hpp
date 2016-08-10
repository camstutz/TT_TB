/*!
 * @file trigger_tower.hpp
 * @author Christian Amstutz
 * @date August 4, 2016
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "pattern_bank/pattern_bank.hpp"
#include "../data_organizer/data_organizer.hpp"
#include "../processor_organizer/processor_organizer.hpp"
#include "../am_board/am_board.hpp"

#include "trigger_tower_config.hpp"

#include "sc_map.hpp"

#include <systemc.h>

#include <sstream>

/*!
 * @brief
 */
class trigger_tower : public sc_module
{
private:
    const trigger_tower_config* configuration;

public:
    const unsigned int layer_nr;
    const unsigned int prb_nr;
    const unsigned int dtc_per_prb;
    const unsigned int AM_boards_per_proc_unit;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_map_list<unsigned int, sc_in<data_organizer::dtc_input_t> > dtc_inputs;
    sc_map_cube<sc_out<am_board::output_stream_t> > hit_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_map_square<sc_buffer<data_organizer::proc_unit_output_t > > trigger_tower_interconnect;
    sc_map_cube<sc_buffer<processor_organizer::processor_output_t> > am_board_in_sig;

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    sc_map_linear<data_organizer> dataOrganizers;
    sc_map_linear<processor_organizer> processorOrganizers;
    sc_map_square<am_board> amBoards;

    pattern_bank patternBank;
    module_address_lookup moduleAddressLookup;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    trigger_tower(sc_module_name _name, const trigger_tower_config&);
};
