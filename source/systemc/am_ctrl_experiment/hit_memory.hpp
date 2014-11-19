/*!
 * @file hit_memory.hpp
 * @author Christian Amstutz
 * @date November 17, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <queue>
#include <vector>
#include <list>
#include <utility>

#include <systemc.h>
#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "am_ctrl_exp_config.hpp"
#include "hit_memory_write_ctrl.hpp"
#include "hit_memory_lookup_ctrl.hpp"
#include "hit_memory_output_ctrl.hpp"

/*!
 * @brief
 */
class hit_memory : public sc_module
{
public:
    typedef std::pair<bool, std::list<substrip_t> > superstrip_table_element_t;
    typedef std::map<superstrip_t, superstrip_table_element_t> superstrip_table_t;
    typedef std::vector<superstrip_table_t> event_set_t;
    std::queue<event_set_t> hit_storage;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<superstrip_t> > superstrip_inputs;
    sc_map_linear<sc_in<substrip_t> > substrip_inputs;
    sc_map_linear<sc_in<superstrip_t> > superstrip_search;
    sc_map_linear<sc_out<hit_t> > hit_outputs;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<bool> > process_hits;
    sc_buffer<bool> write_event_begin;
    sc_buffer<bool> write_event_end;
    sc_buffer<bool> transmit_event_begin;

    sc_map_linear<sc_signal<superstrip_t> > pure_superstrips;
    sc_map_linear<sc_fifo<hit_t> > output_buffer;

    // ----- Process Declarations ----------------------------------------------
    void initialize_event();
    void write_buffer();
    void search_hits();
    void write_hits();

    // ----- Other Method Declarations -----------------------------------------
    void print_superstrip_table(superstrip_table_t table);

    // ----- Module Instantiations ---------------------------------------------
    hit_memory_write_ctrl write_controller;
    hit_memory_lookup_ctrl lookup_controller;
    hit_memory_output_ctrl output_controller;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_memory(const sc_module_name _name);
    SC_HAS_PROCESS(hit_memory);
};
