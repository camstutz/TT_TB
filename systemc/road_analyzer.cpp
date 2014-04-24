/*!
 * @file road_analyzer.cpp
 * @author Christian Amstutz
 * @date Apr 24, 2014
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
        hit_cnt("hit_cnt"),
        road_in("road_in"),
        road_cnt(0)
{
    // ----- Process registration ----------------------------------------------
	SC_THREAD(detect_roads);
		sensitive << clk.pos();
	SC_THREAD(update_hit_cnt)
	    sensitive << hit_cnt;

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
    std::cout << hit_counter << " hits analyzed" << std::endl;
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

			if (road_in.read()(29,28) == 0x1)
			{
			    ++road_cnt;
			}
		}
	}

}

// *****************************************************************************
void road_analyzer::update_hit_cnt()
{
    while (1)
    {
        wait();

        hit_counter = hit_cnt.read();
    }
}
