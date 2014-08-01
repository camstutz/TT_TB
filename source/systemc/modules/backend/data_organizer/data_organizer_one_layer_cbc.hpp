/*!
 * @file data_organizer_one_layer_cbc.hpp
 * @author Christian Amstutz
 * @date July 31, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../data_formats/stub_vbxfsb.hpp"
#include "data_organizer_one_layer.hpp"

/*!
 * @brief
 */
class data_organizer_one_layer_cbc : public data_organizer_one_layer
{
public:
    typedef stub_vbxfsb<DC_STUB_BX_BITS,
                        DC_STUB_FE_BITS,
                        FE_CBC_STUB_STRIP_BITS,
                        FE_CBC_STUB_BEND_BITS,
                        DC_STUB_BX_BITS+DC_STUB_FE_BITS+FE_CBC_STUB_STRIP_BITS
                        +FE_CBC_STUB_BEND_BITS> cbc_out_stub_t;

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
    data_organizer_one_layer_cbc(sc_module_name _name);
    SC_HAS_PROCESS(data_organizer_one_layer_cbc);

protected:

    virtual void process_input_buffer();
};
