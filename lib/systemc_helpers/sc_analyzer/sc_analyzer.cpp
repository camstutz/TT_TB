/*!
 * @file sc_analyzer.hpp
 * @author Christian Amstutz
 * @date Feb 19, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "sc_analyzer.hpp"

//******************************************************************************
void sc_analyzer::register_model_setup_start()
{
    setup_start_time = std::chrono::high_resolution_clock::now();

    return;
}

//******************************************************************************
void sc_analyzer::register_model_setup_end()
{
    setup_end_time = std::chrono::high_resolution_clock::now();
    setup_end_registered = true;

    return;
}

//******************************************************************************
void sc_analyzer::register_simulation_start()
{
    simulation_start_time = std::chrono::high_resolution_clock::now();
    if (setup_end_registered == false)
    {
        setup_end_time = simulation_start_time;
    }

    return;
}

//******************************************************************************
void sc_analyzer::register_simulation_end()
{
    simulation_end_time = std::chrono::high_resolution_clock::now();

    return;
}

//******************************************************************************
void sc_analyzer::print_report()
{
    std::chrono::duration<double> setup_time;
    std::chrono::duration<double> simulation_time;

    setup_time = setup_end_time - setup_start_time;
    simulation_time = simulation_end_time - simulation_start_time;

    std::cout << std::dec << std::endl;
    std::cout << "************************************\n";
    std::cout << "SystemC Analysis Report\n";
    std::cout << "************************************" << std::endl;
    std::cout << "Time to create model : " << setup_time.count()   << "s" << std::endl;
    std::cout << "Time to simulate     : " << simulation_time.count() << "s" << std::endl;
    std::cout << "Simulated Time       : " << sc_time_stamp() << std::endl;
    std::cout << "Delta Cycles         : " << sc_delta_count() << std::endl;

    return;
}
