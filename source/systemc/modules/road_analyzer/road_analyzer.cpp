/*!
 * @file road_analyzer.cpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "road_analyzer.hpp"

// *****************************************************************************
road_analyzer::road_analyzer(sc_module_name _name,
        const road_analyzer_config configuration) :
        sc_module(_name),
        filename(configuration.output_file),
        nr_inputs(configuration.nr_inputs),
        nr_layers(configuration.nr_layers),
        hit_cnt("hit_cnt"),
        filtered_hits(nr_inputs, nr_layers, "filtered_hits"),
        hit_counter(0),
        filtered_hits_cnt(0)
{
    // ----- Process registration ----------------------------------------------
	SC_THREAD(detect_hits);
		sensitive << filtered_hits;
	SC_THREAD(update_hit_cnt)
	    sensitive << hit_cnt;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    road_file.open(filename.c_str());

  return;
}

// *****************************************************************************
road_analyzer::~road_analyzer()
{
    road_file.close();

    std::cout << std::endl;
    std::cout << hit_counter << " hits analyzed" << std::endl;
    std::cout << filtered_hits_cnt << " hits written to " << filename << std::endl;

    return;
}

// *****************************************************************************
void road_analyzer::detect_hits()
{
	while (1)
	{
		wait();

        for (unsigned int input_id = 0; input_id < (nr_inputs); ++input_id)
        {
            for (unsigned int layer = 0; layer < nr_layers; ++layer)
            {
                if (filtered_hits.at(input_id, layer).event())
                {
                    track_finder::hit_stream read_hit;
                    read_hit = filtered_hits.at(input_id, layer).read();
                    if (!read_hit.is_opcode())
                    {
                        road_file << sc_time_stamp() << " @ " << input_id
                                  << "," << layer <<" : "
                                  <<  read_hit.get_value() << std::endl;
                        ++filtered_hits_cnt;
                    }
                }
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
