/*!
 * @file hit_generator.hpp
 * @author Christian Amstutz
 * @date Mar 17, 2014
 *
 * @brief
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
#include "data_representations/stub_sb.hpp"

/*!
 * @brief SystemC module that reads hits from a file.
 */
class hit_generator : public sc_module
{
public:
    typedef stub_sb<FE_STUB_STRIP_BITS, FE_STUB_BEND_BITS> hitgen_stub;

// ----- Port Declarations -----------------------------------------------------
    /** 4-dimensional sc_map for the outputs of the stubs. The dimensions are
     * according to the detector structure in the following order: layer, phi,
     * z and front end chip number. The output format is a stub as defined in
     * stub.hpp */
    sc_map_4d<sc_fifo_out<hitgen_stub> > hit_outputs;

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
    hit_generator(sc_module_name _name, std::string hitFileName);
    SC_HAS_PROCESS(hit_generator);

private:
    std::queue<HitEvent> hit_queue;

    /** Reads the hit_file and stores them in the hit_queue where the
     * schedule_hits process reads it from. This function is called from the
     * constructor so the file is only read once at the start of the simulation.
     */
    int readFile(const std::string &hit_file);
};
