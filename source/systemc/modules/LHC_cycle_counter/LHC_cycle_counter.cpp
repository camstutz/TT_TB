/*!
 * @file LHC_cycle_counter.cpp
 * @author Christian Amstutz
 * @date March 12, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "LHC_cycle_counter.hpp"

// *****************************************************************************
LHC_cycle_counter::LHC_cycle_counter(sc_module_name _name) :
        sc_module(_name),
        LHC_clock("LHC_clock"),
        LHC_cycle("LHC_cycle")
{
    // ----- Process registration ----------------------------------------------
	SC_THREAD(update_cnt)
	    sensitive << LHC_clock;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

  return;
}

// *****************************************************************************
void LHC_cycle_counter::update_cnt()
{
    while (1)
    {
        wait();

        LHC_cycle.write(LHC_cycle.read()+1);
    }
}
