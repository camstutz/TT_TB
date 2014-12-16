/*!
 * @file data_organizer_one_layer_mpa.hpp
 * @author Christian Amstutz
 * @date December 15, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "data_organizer_one_layer.hpp"

/*!
 * @brief
 */
class data_organizer_one_layer_mpa : public data_organizer_one_layer
{
public:
    typedef dc_mpa_stub_t stub_t;

// ----- Port Declarations -----------------------------------------------------

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer_one_layer_mpa(sc_module_name _name);
    SC_HAS_PROCESS(data_organizer_one_layer_mpa);

protected:

    virtual void process_input_buffer();
};
