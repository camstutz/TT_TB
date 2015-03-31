/*!
 * @file am_chip.hpp
 * @author Christian Amstutz
 * @date March 30, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <map>
#include <utility>

#include <systemc.h>

#include "../../../../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../simple_stream_protocol.hpp"

#include "../pattern_bank/pattern_bank.hpp"
#include "../../../../../systems/TT_configuration.hpp"
#include "am_chip_read_ctrl.hpp"
#include "am_chip_write_ctrl.hpp"

/*!
 * @brief Associative Memory Module
 *
 * This SystemC module takes the hits on the inputs coming from each layer and
 * analyzes them for roads. The detected roads are written out of the AM board.
 *
 * todo: describe algorithm in detail
 */
class am_chip : public sc_module
{
public:
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;
    typedef simple_stream_protocol<road_t> road_stream;

    /** @brief Data type of the pattern at the input on each layer */
    typedef superstrip_t pattern_t;

    /** @brief Data type of the road at the output of the AM board */
    typedef road_t road_addr_t;

    /** @brief configures the additional cycles of latency needed.
     *
     * The actual SysatemC model of the AM board has a latency of three clock
     * cycles. To model the real chip additional cycles are needed. This
     * constant configures the additional cycles needed.
     */
    //static const unsigned int additonal_latency = AM_BOARD_LATENCY - 3;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;

    sc_map_linear<sc_in<superstrip_stream> > hit_inputs;
    sc_out<road_stream> road_output;

// ----- Local Channel Declarations --------------------------------------------
    sc_map_linear<sc_signal<bool> > process_hits;
    sc_buffer<bool> roads_detected;

    /** @brief Signals if the road output buffer is empty.
     *
     * This signal is true if the road output buffer is empty. Changes
     * asynchronously.
     */
    sc_signal<bool> output_roads_buffer_empty;

    /** @brief Control signal that enables the processing of the roads. */
    sc_buffer<bool> process_roads_sig;

    /** @brief Control signal that enables the writing of the roads. */
    sc_signal<bool> write_roads_sig;

    sc_signal<road_stream> road_output_sig;

// ----- Local Storage Declarations --------------------------------------------
    std::map<pattern_bank::pattern_id_t, std::vector<bool> > match_table;
    sc_fifo<road_addr_t> detected_roads_buffer;

// ----- Process Declarations --------------------------------------------------

    /** @brief Process to read and process the incoming hits.
     *
     * Checking all the inputs. If write enable of the input is true then read
     * the hit and process it. The hit/pattern is looked up in the pattern bank
     * and if it is found the bits representing the matched pattern are set.
     * This process runs indefinitely and is sensitive to the positive edge of
     * the clock.
     */
    void process_incoming_hits();

    /** @brief Process to detect roads in the match table.
     *
     * All the lines in the match table are scanned and if there are hits on a
     * certain number of layers defined as a threshold value
     * (AM_HITS_PER_ROAD_THRESHOLD). The address of the detected road is written
     * to the road output buffer. Finally, the match table is cleared and ready
     * for the next hit.
     * This process runs indefinitely and is sensitive to the positive edge of
     * the process_roads signal.
     */
    void detect_roads();

    /** @brief Process to update the buffer empty signal.
     *
     * Sets the output_roads_buffer_emtpy signal to true when the output buffer
     * is empty.
     * This process runs indefinitely and is sensitive to the write and read
     * events of the output road buffer FIFO.
     */
    void check_detected_road_buffer();

// ----- Other Method Declarations ---------------------------------------------

    /** @brief Prints the content of the pattern bank.
     *
     * This function prints the pattern bank to the console. Used for debugging.
     */
    void print_pattern_bank();

    /** @brief Prints the match table.
     *
     * This function prints the match table to the console. If a bit in the
     * table is set a * is printed at its position in the table. Used for
     * debugging.
     */
    void print_match_table();

// ----- Module Instantiations -------------------------------------------------

    /** @brief The FSM module controls the AM board.
     *
     * Sequences through the different states of the AM board: idle,
     * receive hits, process roads, write roads.
     */
    am_chip_read_ctrl read_controller;
    am_chip_write_ctrl write_controller;

    /** Additional delay for the data ready signal to correct the low latency of
     * the quite high level implementation of the AM chip. */
    sc_delay_signal<road_stream, AM_CHIP_LATENCY> delay_road_output;

// ----- Constructor -----------------------------------------------------------

    /*!
     * @brief Constructor
     *
     * Configures and names the ports and signals of the module. Sets the
     * sensitivity of the processes. Initializes the pattern bank and clears the
     * match table.
     */
    am_chip(sc_module_name _name, pattern_bank *p_bank);
    SC_HAS_PROCESS(am_chip);

private:
    pattern_bank *patterns;

    void clear_match_table();
};
