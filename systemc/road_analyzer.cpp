/*!
 * @file road_analyzer.cpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "road_analyzer.hpp"

// *****************************************************************************

road_analyzer::road_analyzer(sc_module_name _name) :
        sc_module(_name)
{
    // ----- Process registration ------------------------------------------------
	SC_THREAD(detect_roads);
		sensitive << clk.pos();

    // ----- Module variable initialization --------------------------------------

    // ----- Module instance / channel binding -----------------------------------

  return;
}

// *****************************************************************************
void road_analyzer::detect_roads()
{
	while (1)
	{
		wait();
		if (write_en.read() == true)
		{
			std::cout << sc_time_stamp() << ": Road detected - " << std::hex << road_in.read().to_uint() << std::endl;
		}
	}

}
