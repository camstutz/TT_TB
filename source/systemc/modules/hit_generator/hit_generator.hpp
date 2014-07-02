/*!
 * @file hit_generator.hpp
 * @author Christian Amstutz
 * @date July 2, 2014
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

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"
#include "../../data_formats/HitEvent.hpp"
#include "../../data_formats/stub_sb.hpp"
#include "../../data_formats/stub_bxsbp.hpp"

/*!
 * @brief SystemC module that reads hits from a file.
 */
class hit_generator : public sc_module
{
public:
    typedef stub_sb<FE_CBC_STUB_STRIP_BITS,
                    FE_CBC_STUB_BEND_BITS,
                    FE_CBC_STUB_STRIP_BITS+FE_CBC_STUB_BEND_BITS> cbc_stub_t;
    typedef stub_bxsbp<FE_MPA_STUB_BX_BITS,
                       FE_MPA_STUB_STRIP_BITS,
                       FE_MPA_STUB_BEND_BITS,
                       FE_MPA_STUB_PIXEL_BITS,
                       FE_MPA_STUB_BX_BITS+FE_MPA_STUB_STRIP_BITS
                       +FE_MPA_STUB_BEND_BITS+FE_MPA_STUB_PIXEL_BITS> mpa_stub_t;

// ----- Port Declarations -----------------------------------------------------
    /** 4-dimensional sc_map for the outputs of the stubs for the CBC front end
     * chips (2S modules). The dimensions are according to the detector
     * structure in the following order: layer, phi, z and front end chip
     * number.
     */
    sc_map_4d<sc_fifo_out<cbc_stub_t> > cbc_stub_outputs;

    /** 4-dimensional sc_map for the outputs of the stubs for the MPA front end
     * chips (PS modules). The dimensions are according to the detector
     * structure in the following order: layer, phi, z and front end chip
     * number.
     */
    sc_map_4d<sc_fifo_out<mpa_stub_t> > mpa_stub_outputs;

    /** Signal that indicates the number of stubs read from the input file. This
     * is used to analyze the system.
     */
    sc_out<unsigned int> hit_cnt;

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
    unsigned int hit_counter;

    /** Reads the hit_file and stores them in the hit_queue where the
     * schedule_hits process reads it from. This function is called from the
     * constructor so the file is only read once at the start of the simulation.
     */
    int readFile(const std::string &hit_file);
};
