/*!
 * @file hit_buffer_config.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "hit_buffer_write_ctrl_config.hpp"
#include "hit_buffer_lookup_ctrl_config.hpp"
#include "hit_buffer_output_ctrl_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class hit_buffer_config
{
public:
   unsigned int layer_nr;
   unsigned int SS_width_bit;

   hit_buffer_write_ctrl_config hit_buffer_write_ctrl;
   hit_buffer_lookup_ctrl_config hit_buffer_lookup_ctrl;
   hit_buffer_output_ctrl_config hit_buffer_output_ctrl;
};
