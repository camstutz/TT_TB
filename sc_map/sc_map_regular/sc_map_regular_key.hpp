/*!
 * @file sc_map_regular_key.hpp
 * @author Christian Amstutz
 * @date June 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../sc_map_key.hpp"

//******************************************************************************
class sc_map_regular_key : public sc_map_key
{
public:
    typedef int index_type;

    static const index_type default_start_id;

    sc_map_regular_key() {};
    virtual ~sc_map_regular_key() {};

    virtual std::string get_string() const =0;

    virtual bool operator==(const sc_map_key& other_key) const =0;
    virtual bool operator<(const sc_map_key& other_key) const =0;
};
