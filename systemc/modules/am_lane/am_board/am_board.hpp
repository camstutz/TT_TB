/*!
 * @file am_board.hpp
 * @author Christian Amstutz
 * @date May 2, 2014
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
 * @brief Associative Memory Module
 *
 * This SystemC module takes the hits on the different
 */
class am_board : public sc_module
{
public:
    typedef sc_bv<AM_BOARD_PATTERN_WIDTH> pattern_t;
    typedef sc_bv<AM_BOARD_ROAD_WIDTH> road_addr_t;

    static const unsigned int nr_pattern = AM_BOARD_PATTERN_NR;
    static const unsigned int additonal_latency = AM_BOARD_LATENCY - 3;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     *  Input port for the clock signal */
    sc_in<bool> clk;

    /** @brief Reset (not used)
     *
     * Input port for the reset signal.*/
    sc_in<bool> rst;

    /** @brief Initialize Event
     *
     * Input port for signaling the start of an event */
    sc_in<sc_bv<3> > init_ev;

    /** @brief Pattern write enable
     *
     * Linear array of input ports for the write enable signals of the
     * patterns. One input for each layer. */
    sc_map_linear<sc_in<bool> > write_en;

    /** @brief Input Pattern
     *
     * Linear array of input ports for the hit patterns. One input for each
     * layer. The width of this port is defined by the macro
     * AM_BOARD_PATTERN_WIDTH. */
    sc_map_linear<sc_in<pattern_t> > pattern_inputs;

    /** @brief Road Ready
     *
     * Output port to signal that the signal at the road output is valid. */
    sc_out<bool> data_ready;

    /** @brief Output Road Address
     *
     * Output port for the detected roads. The address of the
     * content-addressable memory cell is output The width of this port is
     * defined by the macro AM_BOARD_ROAD_WIDTH. */
    sc_out<road_addr_t> road_output;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<bool> detected_roads_buffer_empty;
    sc_signal<bool> process_roads;
    sc_signal<bool> write_roads_sig;
    sc_signal<bool> output_data_ready_no_delay;
    sc_signal<road_addr_t> output_road_no_delay;

// ----- Local Storage Declarations --------------------------------------------
    std::array<std::array<bool, NR_DETECTOR_LAYERS>, nr_pattern> match_table;
    sc_fifo<road_addr_t> detected_roads_buffer;

// ----- Process Declarations --------------------------------------------------
    void process_incoming_stubs();
    void detect_roads();
    void write_roads();
    void check_detected_road_buffer();

// ----- Other Method Declarations ---------------------------------------------
    void initialize_patterns();
    void print_pattern_bank();
    void print_match_table();

// ----- Module Instantiations -------------------------------------------------
    /** The FSM module controls the AM board. */
    am_board_fsm fsm;

    /** Additional delay for the data ready signal to correct the low latency of
     * the quite high level implementation of the AM board. */
    sc_delay_signal<bool, additonal_latency> latency_correction_data_ready;

    /** Additional delay for the road signal to correct the low latency of
     * the quite high level implementation of the AM board. */
    sc_delay_signal<road_addr_t, additonal_latency> latency_correction_road;

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
