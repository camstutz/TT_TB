/*!
 * @file sc_channel_array.hpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <cstddef>

#include <systemc.h>

#include "sc_com_array.hpp"

template<template<class, sc_writer_policy> class channel_type,
        typename data_type, std::size_t channel_count>
class sc_channel_array : public sc_com_array<
        channel_type<data_type, SC_ONE_WRITER>, channel_count>
{
public:
    sc_channel_array();
    sc_channel_array(const char* name);

private:

};

#include "sc_channel_array.cpp"
