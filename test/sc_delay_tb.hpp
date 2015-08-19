/*!
 * @file sc_delay_tb.hpp
 * @author Christian Amstutz
 * @date August 19, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <iostream>
#include <sstream>

#include <systemc.h>

#include "../sc_delay/include/sc_delay_signal.hpp"


class sc_delay_tb : public sc_module
{
public:
    sc_delay_signal<int> delay_element;
    sc_delay_signal<int> zero_delay;

    sc_signal<int> in_signal;
    sc_signal<int> out_signal;
    sc_signal<int> zerod_out_signal;

    sc_clock clock;

    void create_signal();
    void detect_signal();
    void detect_zerod_signal();

    sc_delay_tb(sc_module_name _name);
    SC_HAS_PROCESS(sc_delay_tb);
    ~sc_delay_tb();

private:
    std::ostringstream log_buffer;
};
