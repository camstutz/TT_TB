/*!
 * @file fifo_manager.hpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "../../TT_configuration.hpp"
#include "../../data_representations/do_out_data.hpp"

#include "fifo_manager_datapath.hpp"

/*!
 * @brief SystemC module
 */
class fifo_manager : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_map_square<sc_in<bool>> stub_valid;
    sc_map_square<sc_in<do_out_data>> stub_in;

    sc_map_square<sc_out<bool>> stub_write_en;
    sc_map_square<sc_out<do_out_data>> stub_out;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    //sc_map_linear<data_organizer_one_layer> do_one_layer_map;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_manager(sc_module_name _name);
    SC_HAS_PROCESS(fifo_manager);

private:

};
