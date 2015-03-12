/*!
 * @file LHC_cycle_counter.hpp
 * @author Christian Amstutz
 * @date March 12, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

/*!
 * @brief
 */
class LHC_cycle_counter : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
	sc_in<bool> LHC_clock;
    sc_out<unsigned int> LHC_cycle;

// ----- Local Channel Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
	void update_cnt();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
	LHC_cycle_counter(sc_module_name _name);
    SC_HAS_PROCESS(LHC_cycle_counter);

private:
};
