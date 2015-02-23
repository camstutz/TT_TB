/*!
 * @file frontend_chip_cbc.hpp
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

#include "../frontend/frontend_chip.hpp"

typedef frontend_chip<fe_mpa_stub_t, fe_mpa_stub_t, MAX_HITS_PER_MPA_FE_CHIP, COLLECTION_CYCLES_MPA_FE_CHIP> frontend_chip_mpa;
