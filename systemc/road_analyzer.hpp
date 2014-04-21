/*!
 * @file road_analyzer.hpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>

#include <systemc.h>

#include "TT_configuration.hpp"

/*!
 * @brief
 */
class road_analyzer : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
	sc_in<bool> clk;
	sc_in<bool> write_en;
	sc_in<sc_bv<21>> road_in;

// ----- Local Channel Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
	void detect_roads();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
	road_analyzer(sc_module_name _name);
    SC_HAS_PROCESS(road_analyzer);

private:

};
