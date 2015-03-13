/*!
 * @file frontend_chip.hpp
 * @author Christian Amstutz
 * @date March 13, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <map>
#include <string>

#include <systemc.h>
#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"

/*!
 * @brief
 */
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
class frontend_chip: public sc_module
{
public:
// ----- Configuration ---------------------------------------------------------
	typedef IN_STUB_T input_stub_t;
	typedef OUT_STUB_T output_stub_t;

    static const unsigned int max_stubs_per_cycle;
    static const unsigned int collection_cycles;
    static const unsigned int total_collected_stubs;

// ----- Port Declarations -----------------------------------------------------
    sc_in<unsigned int> LHC_cycle;
    sc_fifo_in<input_stub_t> stub_input;
    sc_map_linear<sc_out<bool> > data_valid;
    sc_map_linear<sc_out<output_stub_t> > stub_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<output_stub_t> selected_stubs;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void write_hits();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    frontend_chip(const sc_module_name _name);
    SC_HAS_PROCESS(frontend_chip);

private:
	typedef std::multimap<typename output_stub_t::bend_t, output_stub_t> ordering_buffer_t;
	ordering_buffer_t ordered_stubs;

	typedef std::vector<std::vector<input_stub_t> > collection_buffer_t;
    std::vector<collection_buffer_t> collection_buffers;
    sc_event buffer_written;

    void prioritize_hits(collection_buffer_t& collection_buffer);
};

// *****************************************************************************

// *****************************************************************************

template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int frontend_chip<IN_STUB_T, OUT_STUB_T,MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::max_stubs_per_cycle = MAX_STUBS_PER_CYCLE;
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int frontend_chip<IN_STUB_T, OUT_STUB_T,MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::collection_cycles = COLLECTION_CYCLES;
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int frontend_chip<IN_STUB_T, OUT_STUB_T,MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::total_collected_stubs = MAX_STUBS_PER_CYCLE * COLLECTION_CYCLES;

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
frontend_chip<IN_STUB_T, OUT_STUB_T,MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::frontend_chip(const sc_module_name _name) :
        sc_module(_name),
        LHC_cycle("LHC_cycle"),
        stub_input("stub_input"),
        data_valid(max_stubs_per_cycle, "data_valid", 0),
        stub_outputs(max_stubs_per_cycle, "stub_output", 0),
        selected_stubs("selected_stubs", total_collected_stubs)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input);
        sensitive << stub_input.data_written();
    SC_THREAD(write_hits);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <typename IN_STUBS_T, typename OUT_STUBS_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
void frontend_chip<IN_STUBS_T, OUT_STUBS_T,MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::read_input()
{
    collection_buffers.resize(2);
    collection_buffers[0].resize(collection_cycles);
    collection_buffers[1].resize(collection_cycles);

    while (1)
    {
        wait();

        unsigned int buffer_selector = (LHC_cycle / collection_cycles) % 2;
        std::cout << sc_time_stamp() << ": " << buffer_selector << std::endl;
        while (stub_input.num_available() > 0)
        {
            input_stub_t act_stub;
            stub_input.read(act_stub);
            collection_buffers[buffer_selector][LHC_cycle%collection_cycles].push_back(act_stub);

            buffer_written.notify();
        }
    }

}

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
void frontend_chip<IN_STUB_T, OUT_STUB_T,MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::write_hits()
{
    while (1)
    {
        wait(buffer_written);

        bool processed = false;
        while (!processed)
        {
            wait(LHC_cycle.value_changed_event());
            if ((LHC_cycle % collection_cycles) == 0)
            {
                unsigned int buffer_selector = ((LHC_cycle+collection_cycles) / collection_cycles) % 2;

                prioritize_hits(collection_buffers[buffer_selector]);

                while (selected_stubs.num_available() > 0)
                {
                    unsigned int i = 0;
                    while ((i < max_stubs_per_cycle) && (selected_stubs.num_available() > 0))
                    {
                        data_valid.at(i).write(true);
                        stub_outputs.at(i).write(selected_stubs.read());
                        ++i;
                    }

                    wait(LHC_cycle.value_changed_event());

                    data_valid.write_all(0);
                    stub_outputs.write_all(output_stub_t());
                }
                processed = true;
            }
        }
    }

}

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
void frontend_chip<IN_STUB_T, OUT_STUB_T,MAX_STUBS_PER_CYCLE,
        COLLECTION_CYCLES>::prioritize_hits(collection_buffer_t& collection_buffer)
{
	ordered_stubs.clear();

    /* read all the stubs received in the last cycles and store them ordered by
     * the bend into a map */
    for (unsigned int cycle = 0; cycle < collection_cycles; ++cycle)
    {
        while (!collection_buffer[cycle].empty())
        {
            output_stub_t act_stub = collection_buffer[cycle].back();
            collection_buffer[cycle].pop_back();
            act_stub.set_bx(cycle);
            ordered_stubs.insert(typename ordering_buffer_t::value_type(act_stub.get_bend(), act_stub));
        }
    }

    typename ordering_buffer_t::reverse_iterator output_stub_it = ordered_stubs.rbegin();
    for (unsigned int i = 0; i < total_collected_stubs; ++i)
    {
        if (output_stub_it !=  ordered_stubs.rend())
        {
            selected_stubs.write(output_stub_it->second);
            ++output_stub_it;
        }
    }

    if (output_stub_it != ordered_stubs.rend())
    {
        std::cerr << sc_time_stamp() << ": Front End Chip received more than "
                  << total_collected_stubs << " hits in " << collection_cycles
                  << " cycles." << std::endl;
    }
}
