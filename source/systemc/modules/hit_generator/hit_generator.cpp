/*!
 * @file hit_generator.cpp
 * @author Christian Amstutz
 * @date July 2, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_generator.hpp"

// *****************************************************************************

hit_generator::hit_generator(sc_module_name _name , std::string hitFileName) :
        sc_module(_name),
        cbc_stub_outputs(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z,
                NR_FE_CHIP_PER_MODULE, "hit_output", NR_DETECTOR_MPA_LAYERS,0,
                0, 0),
        mpa_stub_outputs(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z,
                NR_FE_CHIP_PER_MODULE, "hit_output", 0, 0, 0),
        hit_cnt("hit_cnt"),
        hit_counter(0)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(schedule_hits);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    readFile(hitFileName);

    return;
}

// *****************************************************************************
void hit_generator::schedule_hits()
{
    hit_cnt.write(0);

    while (!hit_queue.empty())
    {
        sc_time wait_time;
        HitEvent hit;
        cbc_stub_t processed_cbc_stub;
        mpa_stub_t processed_mpa_stub;

        hit = hit_queue.front();
        hit_queue.pop();

        wait_time = (hit.timeStamp * sc_time(LHC_CLOCK_PERIOD_NS, SC_NS));
        wait_time = wait_time - sc_time_stamp();
        if (wait_time > sc_time(0,SC_PS))
        {
            wait(wait_time);
        }

        // stub belongs to a MPA chip
        if (hit.layer < NR_DETECTOR_MPA_LAYERS)
        {
            processed_mpa_stub.set_bx(0);
            processed_mpa_stub.set_strip(hit.stubAddress);
            processed_mpa_stub.set_bend(hit.stubBend);
            processed_mpa_stub.set_pixel(0);
            mpa_stub_outputs.at(hit.layer, hit.phiCoordinate, hit.zCoordinate,
                    hit.frontEndChipNr).write(processed_mpa_stub);
        }
        // stub belongs to a CBC chip
        else
        {
            processed_cbc_stub.set_strip(hit.stubAddress);
            processed_cbc_stub.set_bend(hit.stubBend);
            cbc_stub_outputs.at(hit.layer, hit.phiCoordinate, hit.zCoordinate,
                    hit.frontEndChipNr).write(processed_cbc_stub);
        }

        ++hit_counter;
        hit_cnt.write(hit_counter);

        #ifdef DEBUG
        std::cout << std::hex << sc_time_stamp() << " hit_generator @ "
                << "L" << hit.layer
                << "P" << hit.phiCoordinate
                << "Z" << hit.zCoordinate
                << "FE" << hit.frontEndChipNr
                << " Stub --> 0x"
                << processed_cbc_stub.get_strip() << "/0x"
                << processed_cbc_stub.get_bend() << std::endl;
        #endif
    }

    return;
}

// *****************************************************************************
int hit_generator::readFile(const std::string &hit_file) {

    //! todo: check that input file fits to detector architecture, check for validity of data and adapt to given range if possible

    std::ifstream hitFile;

    hitFile.open(hit_file.c_str());
    if (hitFile.is_open())
    {
        #ifdef DEBUG
        std::cout << "File: " << hit_file << " opened ..." << std::endl;
        #endif

        std::string fileLine;
        HitEvent hit;

        // clear the event queue
        std::queue<HitEvent> empty;
        std::swap(hit_queue, empty);

        // read hits
        while (std::getline(hitFile, fileLine))
        {
            std::stringstream fileLineStream(fileLine);
            fileLineStream >> std::hex >> hit.timeStamp
                           >> hit.layer
                           >> hit.phiCoordinate
                           >> hit.zCoordinate
                           >> hit.frontEndChipNr
                           >> hit.stubAddress
                           >> hit.stubBend;

            /** Assumption: hits are in the correct order in the file. */

            // check for valid stub in the read line
            if ( !fileLineStream.fail() )
            {
                hit_queue.push(hit);
                #ifdef DEBUG
                std::cout << "Hit read -" << std::hex
                          << " TS:0x" << hit.timeStamp
                          << ", Lay:0x" << hit.layer
                          << ", Phi:0x" << hit.phiCoordinate
                          << ", Z:0x" << hit.zCoordinate
                          << ", FE:0x" << hit.frontEndChipNr
                          << ", Stub:0x" << hit.stubAddress
                          << ", Bend:0x" << hit.stubBend
                          << std::endl;
                #endif
            }
        }

        hitFile.close();

        #ifdef DEBUG
        std::cout << "File: " << hit_file << " closed." << std::endl;
        #endif
    }
    else
    {
        std::cout << "File with hits could not be read: " << hit_file << std::endl;
        return (1);
    }

    return (0);
}
