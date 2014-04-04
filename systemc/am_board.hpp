/*!
 * @file am_board.hpp
 * @author Christian Amstutz
 * @date Apr 3, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <array>
#include <vector>
#include <map>

#include <systemc.h>
#include "../lib/systemc_helpers/sc_map/sc_map.hpp"
#include "../lib/systemc_helpers/sc_delay/sc_delay_signal.hpp"

#include "TT_configuration.hpp"

/*!
 * @brief
 */
class am_board : public sc_module
{
public:
    typedef sc_bv<18> pattern_t;
    typedef sc_bv<8> road_addr_t;

    static const unsigned int nr_pattern = 256;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_in<sc_bv<3> > init_ev;
    sc_map_linear<sc_in<bool> > write_en;
    sc_map_linear<sc_in<pattern_t> > pattern_inputs;
    sc_out<bool> data_ready;
    sc_out<road_addr_t> road_output;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<road_addr_t> output_road_no_delay;

// ----- Local Storage Declarations --------------------------------------------
    std::vector<std::array<bool, NR_DETECTOR_LAYERS> > match_table;
    sc_fifo<road_addr_t> detected_roads_buffer;

// ----- Process Declarations --------------------------------------------------
    void process_incoming_stubs();
    void detect_roads();
    void write_roads();

// ----- Other Method Declarations ---------------------------------------------
    void initialize_patterns();

// ----- Module Instantiations -------------------------------------------------
    sc_delay_signal<road_addr_t, 4> latency_corrector;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    am_board(sc_module_name _name);
    SC_HAS_PROCESS(am_board);

private:
    // todo: increase performance by using unordered list
    // todo: try to use pattern_t as key of multimap
    typedef std::multimap<unsigned int, road_addr_t> lay_pattern_bank_t;
    std::array<lay_pattern_bank_t, NR_DETECTOR_LAYERS> pattern_bank;
};
