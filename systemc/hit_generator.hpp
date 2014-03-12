/*!
 * @file hit_generator.hpp
 * @author Christian Amstutz
 * @date Mar 12, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <queue>

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "TT_configuration.hpp"
#include "HitEvent.hpp"
#include "stub.hpp"

/*!
 * @brief
 */
class hit_generator : public sc_module
{
public:

    // ----- Port Declarations ---------------------------------------------------
    sc_map_4d<sc_fifo_out<stub> > hit_outputs;

    // ----- Local Channel Declarations ------------------------------------------

    // ----- Process Declarations ------------------------------------------------
    void schedule_hits();

    // ----- Other Method Declarations -------------------------------------------

    // ----- Module Instantiations -----------------------------------------------

    // ----- Constructor ---------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_generator(sc_module_name _name, std::string hitFileName);
    SC_HAS_PROCESS(hit_generator);

private:
    std::queue<HitEvent> hit_queue;
    int readFile(const std::string &hit_file);
};
