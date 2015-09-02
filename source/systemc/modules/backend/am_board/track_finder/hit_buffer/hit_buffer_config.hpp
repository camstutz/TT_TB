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

#include "../../../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class hit_buffer_config
{
friend class hit_buffer;

private:
   unsigned int layer_nr;
   unsigned int SS_width_bit;

public:

   hit_buffer_write_ctrl_config hit_buffer_write_ctrl;
   hit_buffer_lookup_ctrl_config hit_buffer_lookup_ctrl;
   hit_buffer_output_ctrl_config hit_buffer_output_ctrl;

   hit_buffer_config();

   void set_layer_nr(unsigned int layer_nr);
   void set_SS_width_bit(unsigned int SS_width_bit);
};
