/*!
 * @file po_layer_splitter.hpp
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

#include "../../../data_formats/prbf/PRBF.hpp"

#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

/*!
 * @brief
 */
class po_layer_splitter : public sc_module
{
public:
    typedef PRBF_2 frame_t;
    typedef frame_t::stub_element_t element_t;

    static const unsigned int layer_nr;

// ----- Port Declarations -----------------------------------------------------
    sc_fifo_in<element_t> input_stubs;
    sc_map_linear<sc_fifo_out<element_t> > splitted_stubs;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void split_stubs();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    po_layer_splitter(sc_module_name _name);
    SC_HAS_PROCESS(po_layer_splitter);
};
