/*!
 * @file hit_generator.cpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "hit_generator.hpp"

// *****************************************************************************

hit_generator::hit_generator(sc_module_name _name ,
        const hit_generator_config configuration) :
        sc_module(_name),
        stub_outputs(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z,
                2*NR_FE_CHIP_PER_MODULE, "hit_output"),
        hit_cnt("hit_cnt"),
        configuration(configuration),
        hit_counter(0)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(schedule_hits);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    readFile(configuration.input_file);

    return;
}

// *****************************************************************************
void hit_generator::schedule_hits()
{
    hit_cnt.write(0);

    while (!hit_queue.empty())
    {
        sc_time wait_time;

        HitSF hit = hit_queue.front();
        hit_queue.pop();

        wait_time = (hit.getEvent() * sc_time(LHC_CLOCK_PERIOD_NS, SC_NS));
        wait_time = wait_time - sc_time_stamp();
        if (wait_time > sc_time(0, SC_PS))
        {
            wait(wait_time);
        }

        stub output_stub;

        // stub belongs to an MPA chip
        if (hit.getModuleIsPS())
        {
            output_stub = stub(configuration.output_stub_mpa, true, 0, 0,
                    hit.getStrip(), hit.getBend(), hit.getPixel());
        }
        // stub belongs to a CBC chip
        else
        {
            output_stub = stub(configuration.output_stub_cbc, true, 0, 0,
                    hit.getStrip(), hit.getBend(), 0);
        }

        HitSF::layer_t layer = hit.getLayer();
        HitSF::ladder_t ladder = hit.getLadder();
        HitSF::module_t module_cnt = hit.getModule();
        HitSF::chip_t chip = 2*hit.getSegment() + hit.getChip();

        stub_outputs.at(layer, ladder, module_cnt, chip).write(output_stub);

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
        SYSTEMC_LOG << "File: " << hit_file << " opened ...";

        // clear the event queue
        std::queue<HitSF> empty;
        std::swap(hit_queue, empty);

        // read all the hits from the file
        std::string fileLine;
        while (std::getline(hitFile, fileLine))
        {
            bool line_valid;
            HitSF hit = HitSF(&line_valid, fileLine);

            // check for valid stub in the read line
            if (line_valid)
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

        SYSTEMC_LOG << "File: " << hit_file << " closed.";
    }
    else
    {
        std::cout << "File with hits could not be read: " << hit_file << std::endl;
        return (1);
    }

    return (0);
}
