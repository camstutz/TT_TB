/*!
 * @file am_ctrl_exp_top.hpp
 * @author Christian Amstutz
 * @date December 3, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <utility>
#include <fstream>
#include <sstream>
#include <iomanip>

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
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;
    typedef simple_stream_protocol<substrip_t> substrip_stream;
    typedef simple_stream_protocol<road_t> road_stream;

    static const std::string in_filename;
    static const std::string out_filename;
    static const unsigned int output_width;

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_clock clock;
    sc_map_linear<sc_buffer<hit_stream> > input_hit_sig;
    sc_map_linear<sc_signal<superstrip_stream> > hit_buffer_ss_store_sig;
    sc_map_linear<sc_signal<substrip_stream> > hit_buffer_subs_store_sig;
    sc_map_linear<sc_signal<superstrip_stream> > am_input_sig;
    sc_signal<road_stream> am_output_sig;
    sc_signal<road_t> pattern_mem_addr_sig;
    sc_map_linear<sc_buffer<superstrip_t> > pattern_mem_out_sig;
    sc_map_linear<sc_signal<superstrip_stream> > hit_search_sig;
    sc_map_linear<sc_signal<hit_stream> > hit_result_sig;
    sc_map_linear<sc_signal<hit_stream> > output_hit_sig;

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

    std::ifstream in_file;
    std::ofstream out_file;
};
