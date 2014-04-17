/*!
 * @file tt_tb.hpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "TT_configuration.hpp"
#include "hit_generator.hpp"
#include "sensor_module.hpp"
#include "data_organizer.hpp"
#include "stub_fifo.hpp"
#include "modules/am_controller/am_controller.hpp"
#include "modules/am_board/am_board.hpp"
#include "data_representations/do_out_data.hpp"

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
    sc_map_linear<sc_signal<do_out_data> > do_stubs;

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
    sc_signal<sc_bv<21>> result_road;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    hit_generator hitGenerator;
    sc_map_cube<sensor_module> sensor_modules;
    data_organizer dataOrganizer;
    sc_map_linear<stub_fifo<STUB_FIFO_DEPTH>> stub_fifos;
    am_controller amController;
    am_board amBoard;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    tt_tb(const sc_module_name _name);
    SC_HAS_PROCESS(tt_tb);
};
