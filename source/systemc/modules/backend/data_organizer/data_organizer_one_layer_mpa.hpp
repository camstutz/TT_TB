/*!
 * @file data_organizer_one_layer_mpa.hpp
 * @author Christian Amstutz
 * @date July 30, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../data_formats/stub_vbxpfsb.hpp"
#include "data_organizer_one_layer.hpp"

/*!
 * @brief
 */
class data_organizer_one_layer_mpa : public data_organizer_one_layer
{
public:
    typedef stub_vbxpfsb<DC_STUB_BX_BITS,
                         FE_MPA_STUB_PIXEL_BITS,
                         DC_STUB_FE_BITS,
                         FE_MPA_STUB_STRIP_BITS,
                         FE_MPA_STUB_BEND_BITS,
                         DC_STUB_BX_BITS+FE_MPA_STUB_PIXEL_BITS+DC_STUB_FE_BITS+
                         FE_MPA_STUB_STRIP_BITS+FE_MPA_STUB_BEND_BITS>
                         mpa_out_stub_t;

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
