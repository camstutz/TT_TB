/*!
 * @file am_ctrl_exp_top.hpp
 * @author Christian Amstutz
 * @date November 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <utility>

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "simple_stream_protocol.hpp"

#include "am_ctrl_exp_config.hpp"
#include "hit_processor.hpp"
#include "hit_memory.hpp"
#include "am_chip.hpp"
#include "pattern_memory.hpp"
#include "road_processor.hpp"

/*!
 * @brief
 */
class am_ctrl_exp_top : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_clock clock;
    sc_map_linear<sc_buffer<hit_stream> > input_hit_sig;
    sc_map_linear<sc_signal<superstrip_t> > hit_buffer_ss_store_sig;
    sc_map_linear<sc_signal<substrip_t> > hit_buffer_subs_store_sig;
    sc_map_linear<sc_signal<superstrip_t> > am_input_sig;
    sc_signal<road_t> am_output_sig;
    sc_signal<road_t> pattern_mem_addr_sig;
    sc_map_linear<sc_buffer<superstrip_t> > pattern_mem_out_sig;
    sc_map_linear<sc_signal<superstrip_t> > hit_search_sig;
    sc_map_linear<sc_signal<hit_t> > hit_result_sig;
    sc_map_linear<sc_signal<hit_t> > output_hit_sig;

    // ----- Process Declarations ----------------------------------------------
    void generate_input();
    void log_input();
    void log_result();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    hit_processor hit_proc;
    hit_memory hit_buffer;
    am_chip road_lookup;
    pattern_memory pattern_lookup;
    road_processor road_proc;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_ctrl_exp_top(const sc_module_name _name);
    SC_HAS_PROCESS(am_ctrl_exp_top);
    ~am_ctrl_exp_top();

private:
    std::ostringstream in_log_buffer;
    std::ostringstream out_log_buffer;
};
