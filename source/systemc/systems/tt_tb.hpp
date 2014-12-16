/*!
 * @file tt_tb.hpp
 * @author Christian Amstutz
 * @date December 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <utility>

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../data_formats/fm_out_data.hpp"

#include "TT_configuration.hpp"
#include "../modules/hit_generator/hit_generator.hpp"
#include "../modules/frontend_cbc/sensor_module_cbc.hpp"
#include "../modules/frontend_mpa/sensor_module_mpa.hpp"
#include "../modules/backend/data_organizer/data_organizer.hpp"
#include "../modules/backend/fifo_manager/fifo_manager.hpp"
#include "../modules/backend/am_board/am_board.hpp"
#include "../modules/road_analyzer/road_analyzer.hpp"

/*!
 * @brief
 */
class tt_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_clock LHC_clock;
    sc_clock LHCx4_clock;
    sc_clock AM_clock;
    sc_signal<bool> true_sig;
    sc_map_4d<sc_fifo<hit_generator::mpa_stub_t> > hit_fifos_mpa;
    sc_map_4d<sc_fifo<hit_generator::cbc_stub_t> > hit_fifos_cbc;
    sc_map_cube<sc_signal<sensor_module_cbc::dc_out_t> > fe_signals;

    sc_map_square<sc_signal<bool> > do_dv_sig;
    sc_map_square<sc_signal<data_organizer::do_out_t> > do_stub_out_sig;

    sc_map_square<sc_signal<bool> > fifo_write_en;
    sc_map_square<sc_signal<fm_out_data> > fifo_stub_in;
    sc_map_linear<sc_signal<bool> > result_write_en;
    sc_map_linear<sc_signal<sc_bv<30> > > result_road;

    sc_signal<unsigned int> hit_cnt_sig;

    sc_map_square<sc_signal<bool> > neighbour_dv_in_sink;
    sc_map_square<sc_signal<do_stub_t> > neighbour_stub_in_sink;
    sc_map_square<sc_signal<bool> > neighbour_dv_out_sink;
    sc_map_square<sc_signal<do_stub_t> > neighbour_stub_out_sink;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    hit_generator hitGenerator;
    sc_map_cube<sensor_module_mpa> sensor_modules_mpa;
    sc_map_cube<sensor_module_cbc> sensor_modules_cbc;
    data_organizer dataOrganizer;
    fifo_manager fifoManager;
    sc_map_linear<am_board> am_board_array;
    road_analyzer roadAnalyzer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    tt_tb(const sc_module_name _name);
    SC_HAS_PROCESS(tt_tb);
};
