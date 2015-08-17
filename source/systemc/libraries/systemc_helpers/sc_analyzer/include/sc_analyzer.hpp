/*!
 * @file sc_analyzer.hpp
 * @author Christian Amstutz
 * @date May 21, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#if __cplusplus < 201000
#include "time.h"
#else
#include <chrono>
#endif

#include <iostream>

#include <systemc.h>

//******************************************************************************

class sc_analyzer
{
public:

#if __cplusplus < 201000
    typedef clock_t clock_type;
    typedef clock_t duration_type;
#else
    typedef std::chrono::time_point<std::chrono::system_clock> clock_type;
    typedef std::chrono::duration<double> duration_type;
#endif

    sc_analyzer();

    void register_model_setup_start();
    void register_model_setup_end();
    void register_simulation_start();
    void register_simulation_end();

    void print_report();

private:
    clock_type setup_start_time;
    clock_type setup_end_time;
    clock_type simulation_start_time;
    clock_type simulation_end_time;

    bool setup_end_registered;

    clock_type get_time();
};
