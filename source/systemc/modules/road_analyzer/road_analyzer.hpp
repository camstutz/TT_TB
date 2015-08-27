/*!
 * @file road_analyzer.hpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../backend/am_board/track_finder/track_finder.hpp"
#include "road_analyzer_config.hpp"

#include "sc_map.hpp"

#include <systemc.h>

#include <string>
#include <sstream>
#include <fstream>

// *****************************************************************************
/*!
 * @brief
 */
class road_analyzer : public sc_module
{
public:
    const std::string filename;
    const unsigned int nr_inputs;
    const unsigned int nr_layers;

// ----- Port Declarations -----------------------------------------------------
	sc_in<unsigned int> hit_cnt;
	sc_map_square<sc_in<track_finder::hit_stream> > filtered_hits;

// ----- Local Channel Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
	void detect_hits();
	void update_hit_cnt();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
	road_analyzer(sc_module_name _name, const road_analyzer_config configuration);
    SC_HAS_PROCESS(road_analyzer);
    ~road_analyzer();

private:
    ofstream road_file;
    unsigned int hit_counter;
    unsigned int filtered_hits_cnt;
};
