/*!
 * @file road_analyzer.cpp
 * @author Christian Amstutz
 * @date Apr 22, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "road_analyzer.hpp"

// *****************************************************************************

const std::string road_analyzer::filename = "roads.txt";

// *****************************************************************************
road_analyzer::road_analyzer(sc_module_name _name) :
        sc_module(_name)
{
    // ----- Process registration ----------------------------------------------
	SC_THREAD(detect_roads);
		sensitive << clk.pos();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    road_file.open(filename);

  return;
}

// *****************************************************************************
road_analyzer::~road_analyzer()
{
    road_file.close();

    std::cout << std::endl;
    std::cout << "Results written in " << filename << std::endl;

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
			std::cout << sc_time_stamp() << ": Road detected - "
			        << std::hex << road_in.read().to_uint() << std::endl;
			road_file << std::hex <<road_in.read().to_uint() << std::endl;
		}
	}

}
