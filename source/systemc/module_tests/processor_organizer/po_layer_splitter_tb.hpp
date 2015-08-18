/*!
 * @file po_layer_splitter_tb.hpp
 * @author Christian Amstutz
 * @date April 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/processor_organizer/po_layer_splitter.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class po_layer_splitter_tb : public sc_module
{
public:
    typedef po_layer_splitter::element_t element_t;

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_fifo<element_t> stub_input_sig;
    sc_map_linear<sc_fifo<element_t> > stub_output_sigs;

    // ----- Process Declarations ----------------------------------------------
    void write_stubs();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    po_layer_splitter dut_po_layer_splitter;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    po_layer_splitter_tb(sc_module_name _name, po_layer_splitter_config configuration);
    SC_HAS_PROCESS(po_layer_splitter_tb);
    ~po_layer_splitter_tb();

private:
    std::ostringstream log_buffer;
};
