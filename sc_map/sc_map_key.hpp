/*!
 * @file sc_map_key.hpp
 * @author Christian Amstutz
 * @date May 28, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>
#include <functional>
#include <ostream>

//******************************************************************************
class sc_map_key
{
public:
    class Comperator : public std::binary_function<sc_map_key&, sc_map_key&, bool>
    {
    public:
        bool operator()(const sc_map_key& lhs, const sc_map_key& rhs) const;
    };

    virtual ~sc_map_key() {};

    virtual std::string get_string() const =0;

    virtual bool operator==(const sc_map_key& other_key) const =0;
    virtual bool operator!=(const sc_map_key& other_key) const;
    virtual bool operator<(const sc_map_key& other_key) const =0;
    virtual bool operator>(const sc_map_key& other_key) const;
    virtual bool operator<=(const sc_map_key& other_key) const;
    virtual bool operator>=(const sc_map_key& other_key) const;
};

std::ostream& operator<< (std::ostream& out, const sc_map_key& key);
