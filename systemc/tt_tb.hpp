/*!
 * @file tt_tb.hpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
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

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    hit_generator hitGenerator;
    sc_map_cube<sensor_module> sensor_modules;
    data_organizer dataOrganizer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    tt_tb(const sc_module_name _name);
    SC_HAS_PROCESS(tt_tb);
};
