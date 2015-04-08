/*!
 * @file data_concentrator_cbc.hpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once


#include "../../systems/TT_configuration.hpp"

#include "../frontend/data_concentrator.hpp"

typedef data_concentrator<fe_cbc_stub_t, NR_FE_CHIP_PER_MODULE,
        MAX_HITS_PER_CBC_FE_CHIP, COLLECTION_CYCLES_CBC_FE_CHIP, dc_cbc_out_t,
        NR_DC_CBC_OUT_STUBS, NR_DC_WINDOW_CYCLES> data_concentrator_cbc;
