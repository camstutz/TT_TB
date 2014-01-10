/*!
 * @file FE_DataFormat.hpp
 * @author Christian Amstutz
 * @date Jan 10, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "TT_configuration.hpp"

/*!
 * @brief
 */
struct hit_data_type {
  int address;
  int bend;
};

/*!
 * @brief
 */
struct FE_DataFormat {
  hit_data_type hit_data[NR_HITS_PER_FE_CHIP];
};
