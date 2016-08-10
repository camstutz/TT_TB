/*!
 * @file po_layer_splitter.hpp
 * @author Christian Amstutz
 * @date September 14, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/prbf/PRBF.hpp"
#include "../../../TT_configuration/prbf_module_address.hpp"
#include "../trigger_tower/module_address_lookup/module_address_lookup.hpp"

#include "po_layer_splitter_config.hpp"

#include "sc_map.hpp"

#include <systemc.h>

#include <iostream>
#include <iterator>

/*!
 * @brief
 */
class po_layer_splitter : public sc_module
{
public:
    typedef PRBF_2 frame_t;
    typedef frame_t::stub_element_t element_t;

    const po_layer_splitter_config configuration;

// ----- Port Declarations -----------------------------------------------------
    sc_fifo_in<element_t> input_stubs;
    sc_map_linear<sc_fifo_out<element_t> > splitted_stubs;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void split_stubs();

// ----- Other Method Declarations ---------------------------------------------
    void set_address_lookup(module_address_lookup* address_lu);

// ----- Module Instantiations -------------------------------------------------
    module_address_lookup* addressLookup;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    po_layer_splitter(sc_module_name _name, po_layer_splitter_config);
    SC_HAS_PROCESS(po_layer_splitter);
};
