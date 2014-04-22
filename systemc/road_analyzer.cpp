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
        sc_module(_name),
        clk("clk"),
        write_en("write_en"),
        road_in("road_in"),
        road_cnt(0)
{
    // ----- Process registration ----------------------------------------------
	SC_THREAD(detect_roads);
		sensitive << clk.pos();
	SC_THREAD(detect_road_end);
	    sensitive << write_en;

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
    std::cout << road_cnt << " roads written to " << filename << std::endl;

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
			++road_cnt;
		}
	}

}

// *****************************************************************************
void road_analyzer::detect_road_end()
{
    while (1)
    {
        wait();

        if (write_en.negedge())
        {
            --road_cnt;
        }
    }
}
