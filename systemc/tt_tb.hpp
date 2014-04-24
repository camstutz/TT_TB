/*!
 * @file tt_tb.hpp
 * @author Christian Amstutz
 * @date Apr 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "data_representations/do_out_data.hpp"

#include "TT_configuration.hpp"
#include "hit_generator.hpp"
#include "modules/sensor_module_ss/sensor_module_ss.hpp"
#include "modules/data_organizer/data_organizer.hpp"
#include "stub_fifo.hpp"
#include "modules/am_controller/am_controller.hpp"
#include "modules/am_board/am_board.hpp"
#include "road_analyzer.hpp"


/*!
 * @brief
 */
class tt_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_clock LHC_clock;
    sc_signal<bool> true_sig;
    sc_map_4d<sc_fifo<hit_generator::hitgen_stub_t> > hit_fifos;
    sc_map_cube<sc_signal<sc_bv<DC_OUTPUT_WIDTH> > > fe_signals;

    sc_map_linear<sc_signal<bool>> fifo_not_empty;
    sc_map_linear<sc_buffer<do_out_data>> fifo_stub_in;
    sc_map_linear<sc_signal<bool>> fifo_read_en;
    sc_map_linear<sc_signal<do_out_data>> fifo_stub_out;

    sc_signal<sc_bv<3>> am_init_ev;
    sc_map_linear<sc_signal<bool>> am_write_en;
    sc_map_linear<sc_signal<sc_bv<18>>> am_stubs_in;
    sc_signal<bool> am_data_ready;
    sc_signal<sc_bv<21>> am_road;
    sc_signal<bool> result_write_en;
    sc_signal<sc_bv<30>> result_road;

    sc_signal<unsigned int> hit_cnt_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    hit_generator hitGenerator;
    sc_map_cube<sensor_module_ss> sensor_modules;
    data_organizer dataOrganizer;
    sc_map_linear<stub_fifo<STUB_FIFO_DEPTH>> stub_fifos;
    am_controller amController;
    am_board amBoard;
    road_analyzer roadAnalyzer;


    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    tt_tb(const sc_module_name _name);
    SC_HAS_PROCESS(tt_tb);
};
