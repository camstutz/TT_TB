/*!
 * @file hit_generator.hpp
 * @author Christian Amstutz
 * @date September 23, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../data_formats/HitSF/HitSF.h"
#include "../../data_formats/stub/stub.hpp"
#include "../frontend/sensor_module/chip_address.hpp"

#include "hit_generator_config.hpp"

#include "../../systems/tt_tb_logger.hpp"
#include "sc_map.hpp"

#include <systemc.h>

#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

/*!
 * @brief SystemC module that reads hits from a file.
 */
class hit_generator : public sc_module
{
public:
    // todo: add counter for undelivered stubs

// ----- Port Declarations -----------------------------------------------------
    /** 4-dimensional sc_map for the outputs of the stubs for the front end
     * chips. The dimensions are according to the detector
     * structure in the following order: layer, ladder, module and front end chip
     * number.
     */
    sc_map_list<chip_address, sc_fifo_out<stub> > stub_outputs;

    /** Signal that indicates the number of stubs read from the input file. This
     * is used to analyze the system.
     */
    sc_out<unsigned int> hits_accepted;
    sc_out<unsigned int> hits_discarded;

// ----- Local Channel Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    /** Schedules the hits in the hit_queue and dispatches them to the according
     * front end chip. */
    void schedule_hits();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor: Calls the function for reading the hit file.
     */
    hit_generator(sc_module_name _name, hit_generator_config);
    SC_HAS_PROCESS(hit_generator);

private:
    hit_generator_config configuration;

    std::queue<HitSF> hit_queue;

    unsigned int hits_accepted_cnt;
    unsigned int hits_discarded_cnt;

    /** Reads the hit_file and stores them in the hit_queue where the
     * schedule_hits process reads it from. This function is called from the
     * constructor so the file is only read once at the start of the simulation.
     */
    int readFile(const std::string &hit_file);
};
