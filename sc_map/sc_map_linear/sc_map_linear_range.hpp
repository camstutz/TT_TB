/*!
 * @file sc_map_linear_range.hpp
 * @author Christian Amstutz
 * @date June 9, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_linear_key.hpp"
#include <vector>
#include "../sc_map_regular/sc_map_regular_range.hpp"

//******************************************************************************
class sc_map_linear_range : public sc_map_regular_range<sc_map_linear_key>
{
public:
    using sc_map_range::key_type;

    sc_map_linear_range();
    sc_map_linear_range(key_type start_key, key_type end_key);
    sc_map_linear_range(sc_map_range<key_type>*, key_type start_key, key_type end_key);
    virtual ~sc_map_linear_range() {};

    virtual sc_map_linear_range* clone() const;

    virtual bool next_key(key_type& key) const;
};
