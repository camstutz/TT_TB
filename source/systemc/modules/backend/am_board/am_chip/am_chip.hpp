/*!
 * @file am_chip.hpp
 * @author Christian Amstutz
 * @date Janaury 5, 2015
 *
 * @brief File containing the definition of the AM board.
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <map>
#include <utility>

#include <systemc.h>
#include "../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"

#include "../../../../systems/TT_configuration.hpp"
#include "am_chip_fsm.hpp"

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
    /** @brief Data type of the pattern at the input on each layer */
    typedef sc_bv<AM_BOARD_PATTERN_WIDTH> pattern_t;

    /** @brief Data type of the road at the output of the AM board */
    typedef sc_bv<AM_BOARD_ROAD_WIDTH> road_addr_t;

    /** @brief configures the number of pattern that the AM board contains. */
    static const unsigned int nr_pattern = AM_BOARD_PATTERN_NR;

    /** @brief configures the additional cycles of latency needed.
     *
     * The actual SysatemC model of the AM board has a latency of three clock
     * cycles. To model the real chip additional cycles are needed. This
     * constant configures the additional cycles needed.
     */
    static const unsigned int additonal_latency = AM_BOARD_LATENCY - 3;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;

    /** @brief Initialize Event
     *
     * Input port for signaling the start of an event.
     */
    sc_in<sc_bv<3> > init_ev;

    /** @brief Pattern write enable
     *
     * Linear array of input ports for the write enable signals of the
     * patterns. One input for each layer.
     */
    sc_map_linear<sc_in<bool> > write_en;

    /** @brief Input Pattern
     *
     * Linear array of input ports for the hit patterns. One input for each
     * layer. The width of this port is defined by the macro
     * AM_BOARD_PATTERN_WIDTH.
     */
    sc_map_linear<sc_in<pattern_t> > pattern_inputs;

    /** @brief Road Ready
     *
     * Output port to signal that the signal at the road output is valid.
     */
    sc_out<bool> data_ready;

    /** @brief Output Road Address
     *
     * Output port for the detected roads. The address of the
     * content-addressable memory cell is output The width of this port is
     * defined by the macro AM_BOARD_ROAD_WIDTH.
     */
    sc_out<road_addr_t> road_output;

// ----- Local Channel Declarations --------------------------------------------
    /** @brief Signals if the road output buffer is empty.
     *
     * This signal is true if the road output buffer is empty. Changes
     * asynchronously.
     */
    sc_signal<bool> output_roads_buffer_empty;

    /** @brief Control signal that enables the processing of the roads. */
    sc_signal<bool> process_roads_sig;

    /** @brief Control signal that enables the writing of the roads. */
    sc_signal<bool> write_roads_sig;

    /** @brief Undelayed data ready output
     *
     * Data ready signal generated by the AM board without delay. To model the
     * real AM chip the signal is output after a delay.
     */
    sc_signal<bool> output_data_ready_no_delay;

    /** @brief Undelayed road output
     *
     * Road signal generated by the AM board without delay. To model the
     * real AM chip the signal is output after a delay.
     */
    sc_signal<road_addr_t> output_road_no_delay;

// ----- Local Storage Declarations --------------------------------------------
    std::vector<std::vector<bool> > match_table;
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

    /** @brief Process to write the roads to the output buffer.
     *
     * If the FSM indicates that roads should be written and there are roads in
     * the output buffer, the data ready for the output is set to true and a
     * road from the buffer is output. The output will be read by the delay
     * modules which add some additional delay.
     * This process runs indefinitely and is sensitive to the positive edge of
     * the clock and the positive edge of the write_roads_sig.
     */
    void write_roads();

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
    am_chip_fsm fsm;

    /** Additional delay for the data ready signal to correct the low latency of
     * the quite high level implementation of the AM board. */
    sc_delay_signal<bool, additonal_latency> latency_correction_data_ready;

    /** Additional delay for the road signal to correct the low latency of
     * the quite high level implementation of the AM board.
     */
    sc_delay_signal<road_addr_t, additonal_latency> latency_correction_road;

// ----- Constructor -----------------------------------------------------------

    /*!
     * @brief Constructor
     *
     * Configures and names the ports and signals of the module. Sets the
     * sensitivity of the processes. Initializes the pattern bank and clears the
     * match table.
     */
    am_chip(sc_module_name _name);
    SC_HAS_PROCESS(am_chip);

private:
    // todo: try to use pattern_t as key of multimap
    typedef std::multimap<unsigned int, road_addr_t> lay_pattern_bank_t;
    std::vector<lay_pattern_bank_t> pattern_bank;

    /** @brief Initializes pattern banks
     *
     * This function initializes the pattern bank inside the AM controller.
     * The actual version creates patterns that have all their hits in the same
     * strip on the different layers. Phi and Z are set to 0.
     */
    void initialize_patterns();

    void clear_match_table();
};
