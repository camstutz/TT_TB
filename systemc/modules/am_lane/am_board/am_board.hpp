/*!
 * @file am_board.hpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
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
#include "../../../../lib/systemc_helpers/sc_map/sc_map.hpp"
#include "../../../../lib/systemc_helpers/sc_delay/sc_delay_signal.hpp"

#include "../../../TT_configuration.hpp"
#include "am_board_fsm.hpp"

/*!
 * @brief
 */
class am_board : public sc_module
{
public:
    typedef sc_bv<18> pattern_t;
    typedef sc_bv<21> road_addr_t;

    // todo: pattern number needs to be generic
    static const unsigned int nr_pattern = 255;

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
    sc_signal<bool> detected_roads_buffer_empty;
    sc_signal<bool> process_roads;
    sc_signal<bool> write_roads_sig;
    sc_signal<bool> output_data_ready_no_delay;
    sc_signal<road_addr_t> output_road_no_delay;

// ----- Local Storage Declarations --------------------------------------------
    // todo: pattern number needs to be generic
    std::array<std::array<bool, NR_DETECTOR_LAYERS>, nr_pattern> match_table;
    sc_fifo<road_addr_t> detected_roads_buffer;

// ----- Process Declarations --------------------------------------------------
    void process_incoming_stubs();
    void detect_roads();
    void write_roads();
    void check_detected_road_buffer();

// ----- Other Method Declarations ---------------------------------------------
    void initialize_patterns();

// ----- Module Instantiations -------------------------------------------------
    am_board_fsm fsm;
    sc_delay_signal<bool, 15> latency_cor_data_ready;
    sc_delay_signal<road_addr_t, 15> latency_cor_road;

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
