/*!
 * @file data_concentrator_mpa.hpp
 * @author Christian Amstutz
 * @date April 8, 2015
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

typedef data_concentrator<fe_mpa_stub_t, NR_FE_CHIP_PER_MODULE,
        MAX_HITS_PER_MPA_FE_CHIP, COLLECTION_CYCLES_MPA_FE_CHIP, dc_mpa_out_t,
        NR_DC_MPA_OUT_STUBS, NR_DC_WINDOW_CYCLES> data_concentrator_mpa;
