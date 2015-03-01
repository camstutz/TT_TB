/*!
 * @file data_concentrator_cbc.hpp
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

typedef data_concentrator<fe_cbc_stub_t, dc_cbc_stub_t, MAX_HITS_PER_CBC_FE_CHIP, COLLECTION_CYCLES_CBC_FE_CHIP> data_concentrator_cbc;
