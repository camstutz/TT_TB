/*!
 * @file sc_map.hpp
 * @author Christian Amstutz
 * @date May 5, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"
#include "sc_map_linear.hpp"
#include "sc_map_square.hpp"
#include "sc_map_cube.hpp"
#include "sc_map_4d.hpp"

#include "sc_map_iterator.hpp"
#include "sc_map_iter_sequential.hpp"
#include "sc_map_iter_square.hpp"
#include "sc_map_iter_cube.hpp"
#include "sc_map_iter_4d.hpp"

#include <limits>

namespace sc_map
{
    const sc_map_base<bool>::key_type max = std::numeric_limits<sc_map_base<bool>::key_type>::max();
}
