/*!
 * @file sc_map_4d_key.hpp
 * @author Christian Amstutz
 * @date June 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../sc_map_regular/sc_map_regular_key.hpp"
#include "../sc_map_config.hpp"

#include <string>
#include <sstream>

//******************************************************************************

class sc_map_4d_key : public sc_map_regular_key
{
public:
    using sc_map_regular_key::index_type;

    index_type Z;
    index_type Y;
    index_type X;
    index_type W;

    sc_map_4d_key();
    sc_map_4d_key(const index_type& Z, const index_type& Y, const index_type& X, const index_type& W);
    virtual ~sc_map_4d_key() {};

    virtual std::string get_string() const;

    virtual bool operator==(const sc_map_key& other_key) const;
    virtual bool operator<(const sc_map_key& other_key) const;
};
