/*!
 * @file road_analyzer.hpp
 * @author Christian Amstutz
 * @date Apr 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <fstream>

#include <systemc.h>
#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"

/*!
 * @brief
 */
class road_analyzer : public sc_module
{
public:
    static const std::string filename;

// ----- Port Declarations -----------------------------------------------------
	sc_in<bool> clk;
	sc_map_linear<sc_in<bool> > write_en;

	sc_in<unsigned int> hit_cnt;
	sc_map_linear<sc_in<sc_bv<30> > > road_in;

// ----- Local Channel Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
	void detect_roads();
	void update_hit_cnt();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
	road_analyzer(sc_module_name _name);
    SC_HAS_PROCESS(road_analyzer);
    ~road_analyzer();

private:
    ofstream road_file;
    unsigned int hit_counter;
    unsigned int road_cnt;
};
