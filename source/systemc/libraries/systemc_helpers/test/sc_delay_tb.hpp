/*!
 * @file sc_delay_tb.hpp
 * @author Christian Amstutz
 * @date Apr 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iostream>
#include <sstream>

#include <systemc.h>

#include "../sc_delay/sc_delay_signal.hpp"


class sc_delay_tb : public sc_module
{
public:
    sc_delay_signal<int, 3> delay_element;

    sc_signal<int> in_signal;
    sc_signal<int> out_signal;

    sc_clock clock;

    void create_signal();
    void detect_signal();

    sc_delay_tb(sc_module_name _name);
    SC_HAS_PROCESS(sc_delay_tb);
    ~sc_delay_tb();

private:
    std::ostringstream log_buffer;
};
