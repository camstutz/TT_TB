/*!
 * @file hit_generator.cpp
 * @author Christian Amstutz
 * @date September 23, 2015
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
        stub_outputs(configuration.chip_addresses, "hit_output"),
        hits_accepted("hits_accepted"),
        hits_discarded("hits_discarded"),
        configuration(configuration),
        hits_accepted_cnt(),
        hits_discarded_cnt()
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
    hits_accepted.write(hits_accepted_cnt);
    hits_discarded.write(hits_discarded_cnt);

    while (!hit_queue.empty())
    {
        sc_time wait_time;

        HitSF hit = hit_queue.front();
        hit_queue.pop();

        wait_time = (hit.getEvent() * sc_time(configuration.LHC_clock_period_ns, SC_NS));
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
        HitSF::segment_t segment = hit.getSegment();
        HitSF::chip_t chip = hit.getChip();

        // check if sensor module exists in system
        chip_address hit_chip_address(layer, ladder, module_cnt, segment, chip);
        if (std::find(configuration.chip_addresses.begin(),
                      configuration.chip_addresses.end(),
                      hit_chip_address)
            != configuration.chip_addresses.end())
        {
            ++hits_accepted_cnt;

            if (!stub_outputs.at(hit_chip_address).nb_write(output_stub))
            {
                std::cerr << sc_time_stamp() << ": FIFO overflow @ "
                          << name() << ".stub_outputs[" << hit_chip_address << "]"
                          << std::endl;
            }
            else
            {
                //SYSTEMC_LOG << "Stub sent to: " << hit_chip_address;
            }
        }
        else
        {
            ++hits_discarded_cnt;

//            SYSTEMC_LOG << "Stub cannot be sent to: "
//                        << layer << "," << ladder << "," << module_cnt
//                        << ". Module does not exist.";
        }

        hits_accepted.write(hits_accepted_cnt);
        hits_discarded.write(hits_discarded_cnt);

        #ifdef DEBUG
        std::cout << std::hex << sc_time_stamp() << " hit_generator @ "
                << "Lay" << layer
                << "Lad" << ladder
                << "M"   << module_cnt
                << "FE"  << chip
                << " Stub --> 0x"
                << output_stub.get_strip() << "/0x"
                << output_stub.get_bend() <<  "/0x"
                << output_stub.get_pixel() << std::endl;
        #endif
    }

    return;
}

// *****************************************************************************
int hit_generator::readFile(const std::string &hit_file)
{
    //! todo: check that input file fits to detector architecture, check for validity of data and adapt to given range if possible

    std::ifstream hitFile;

    hitFile.open(hit_file.c_str());
    if (hitFile.is_open())
    {
        //SYSTEMC_LOG << "File: " << hit_file << " opened ...";

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
                          << " TS:0x" << hit.getEvent()
                          << ", Lay:0x" << hit.getLayer()
                          << ", Lad:0x" << hit.getLadder()
                          << ", Mod:0x" << hit.getModule()
                          << ", FE:0x" << hit.getChip()
                          << ", Strip:0x" << hit.getStrip()
                          << ", Pix:0x" << hit.getPixel()
                          << ", Bend:0x" << hit.getBend()
                          << std::endl;
                #endif
            }

        }

        hitFile.close();

        //SYSTEMC_LOG << "File: " << hit_file << " closed.";
    }
    else
    {
        std::cout << "File with hits could not be read: " << hit_file << std::endl;
        return (1);
    }

    return (0);
}
