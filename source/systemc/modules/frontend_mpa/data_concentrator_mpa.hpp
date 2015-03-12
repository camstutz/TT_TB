/*!
 * @file data_concentrator_mpa.hpp
 * @author Christian Amstutz
 * @date February 23, 2015
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

typedef data_concentrator<fe_mpa_stub_t, dc_mpa_stub_t, MAX_HITS_PER_MPA_FE_CHIP, NR_DC_WINDOW_CYCLES> data_concentrator_mpa;
