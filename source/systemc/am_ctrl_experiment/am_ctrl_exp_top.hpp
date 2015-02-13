/*!
 * @file am_ctrl_exp_top.hpp
 * @author Christian Amstutz
 * @date February 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "simple_stream_protocol.hpp"

#include "track_finder/track_finder.hpp"

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
    sc_map_linear<sc_signal<hit_stream> > output_hit_sig;

    // ----- Process Declarations ----------------------------------------------
    void generate_input();
    void log_input();
    void log_result();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    track_finder am_board;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_ctrl_exp_top(const sc_module_name _name);
    SC_HAS_PROCESS(am_ctrl_exp_top);
    ~am_ctrl_exp_top();

private:
    struct hitfile_data_t
    {
        unsigned int event;
        unsigned int layer;
        unsigned int superstrip;
        unsigned int stub;
    };

    struct hitfile_element{
        bool dv;
        hitfile_data_t data;
    };

    struct hitfile_line {
        unsigned int timestamp;
        std::vector<hitfile_element> hits;
    };

    std::queue<hitfile_line> hit_queue;

    std::ostringstream in_log_buffer;
    std::ostringstream out_log_buffer;

    std::ifstream in_file;
    std::ofstream out_file;

    void read_hitfile();
};
