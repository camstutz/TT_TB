/*!
 * @file tt_tb.hpp
 * @author Christian Amstutz
 * @date May 20, 2014
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
#include "../modules/backend/data_organizer/data_organizer.hpp"
#include "../modules/backend/fifo_manager/fifo_manager.hpp"
#include "../modules/backend/am_controller/am_lane.hpp"
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
    sc_map_4d<sc_fifo<hit_generator::hitgen_stub_t> > hit_fifos;
    sc_map_cube<sc_signal<sc_bv<DC_OUTPUT_WIDTH> > > fe_signals;

    sc_map_square<sc_signal<do_out_data> > do_stub_out_sig;

    sc_map_square<sc_signal<fm_out_data> > fifo_stub_in;
    sc_map_linear<sc_signal<bool> > result_write_en;
    sc_map_linear<sc_signal<sc_bv<30> > > result_road;

    sc_signal<unsigned int> hit_cnt_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    hit_generator hitGenerator;
    sc_map_cube<sensor_module_cbc> sensor_modules;
    data_organizer dataOrganizer;
    fifo_manager fifoManager;
    sc_map_linear<am_lane> am_lane_array;
    road_analyzer roadAnalyzer;


    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    tt_tb(const sc_module_name _name);
    SC_HAS_PROCESS(tt_tb);
};
