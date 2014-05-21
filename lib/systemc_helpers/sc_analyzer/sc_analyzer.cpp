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

#include "sc_analyzer.hpp"

//******************************************************************************
sc_analyzer::sc_analyzer() : setup_end_registered(false)
{}

//******************************************************************************
void sc_analyzer::register_model_setup_start()
{
    setup_start_time = get_time();

    return;
}

//******************************************************************************
void sc_analyzer::register_model_setup_end()
{
    setup_end_time = get_time();
    setup_end_registered = true;

    return;
}

//******************************************************************************
void sc_analyzer::register_simulation_start()
{
    simulation_start_time = get_time();
    if (setup_end_registered == false)
    {
        setup_end_time = simulation_start_time;
    }

    return;
}

//******************************************************************************
void sc_analyzer::register_simulation_end()
{
    simulation_end_time = get_time();

    return;
}

//******************************************************************************
void sc_analyzer::print_report()
{
    double setup_time_display;
    double simulation_time_display;

    duration_type setup_time = setup_end_time - setup_start_time;
    duration_type simulation_time = simulation_end_time - simulation_start_time;

#if __cplusplus < 201000
    setup_time_display = (double)setup_time/CLOCKS_PER_SEC;
    simulation_time_display = (double)simulation_time/CLOCKS_PER_SEC;
#else
    setup_time_display = setup_time.count();
    simulation_time_display = simulation_time.count();
#endif

    std::cout << std::dec << std::endl;
    std::cout << "************************************\n";
    std::cout << "SystemC Analysis Report\n";
    std::cout << "************************************" << std::endl;
    std::cout << "Time to create model : " << setup_time_display   << "s" << std::endl;
    std::cout << "Time to simulate     : " << simulation_time_display << "s" << std::endl;
    std::cout << "Simulated Time       : " << sc_time_stamp() << std::endl;
    std::cout << "Delta Cycles         : " << sc_delta_count() << std::endl;

    return;
}

//******************************************************************************
sc_analyzer::clock_type sc_analyzer::get_time()
{
#if __cplusplus < 201000
    return (clock() );
#else
    return (std::chrono::high_resolution_clock::now() );
#endif
}
