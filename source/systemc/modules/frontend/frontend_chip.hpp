/*!
 * @file frontend_chip.hpp
 * @author Christian Amstutz
 * @date June 25, 2015
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

#include "../../TT_configuration/sensor_module_config/fe_chip_output_config.hpp"
#include "../../TT_configuration/sensor_module_config/frontend_chip_config.hpp"

/*!
 * @brief
 */
template <typename IN_STUB_T, typename OUT_STUB_T>
class frontend_chip: public sc_module
{
public:
// ----- Configuration ---------------------------------------------------------
	typedef IN_STUB_T input_stub_t;
	typedef OUT_STUB_T output_stub_t;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
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
    frontend_chip(const sc_module_name _name, frontend_chip_config configuration);
    SC_HAS_PROCESS(frontend_chip);

private:
    unsigned int max_stubs_per_cycle;
    unsigned int collection_cycles;
    unsigned int total_collected_stubs;

	typedef std::multimap<typename output_stub_t::bend_t, output_stub_t> ordering_buffer_t;

	ordering_buffer_t ordered_stubs;
    std::vector<std::vector<input_stub_t> > collection_buffer;

    void prioritize_hits();
};

// *****************************************************************************

typedef frontend_chip<fe_cbc_stub_t, fe_cbc_stub_t> frontend_chip_cbc;

typedef frontend_chip<fe_mpa_stub_t, fe_mpa_stub_t> frontend_chip_mpa;

// *****************************************************************************

// *****************************************************************************

template <typename IN_STUB_T, typename OUT_STUB_T>
frontend_chip<IN_STUB_T, OUT_STUB_T>::frontend_chip(const sc_module_name _name,
        frontend_chip_config configuration) :
        sc_module(_name),
        clk("clk"),
        stub_input("stub_input"),
        data_valid(configuration.max_stubs_per_cycle, "data_valid", 0),
        stub_outputs(configuration.max_stubs_per_cycle, "stub_output", 0),
        selected_stubs("selected_stubs", configuration.max_stubs_per_cycle * configuration.collection_cycles),
        max_stubs_per_cycle(configuration.max_stubs_per_cycle),
        collection_cycles(configuration.collection_cycles),
        total_collected_stubs(configuration.max_stubs_per_cycle * configuration.collection_cycles)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input);
        sensitive << clk.pos();
    SC_THREAD(write_hits);
        sensitive << selected_stubs.data_written_event();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T>
void frontend_chip<IN_STUB_T, OUT_STUB_T>::read_input()
{
    collection_buffer.resize(collection_cycles);

    wait();
    int clock_cycle = -1;

    while (1)
    {
        wait();
        ++clock_cycle;

        while (stub_input.num_available() > 0)
        {
            input_stub_t act_stub;
            stub_input.read(act_stub);
            collection_buffer[clock_cycle].push_back(act_stub);
        }

        if (clock_cycle == collection_cycles-1)
        {
            prioritize_hits();
            clock_cycle = -1;
        }
    }
}

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T>
void frontend_chip<IN_STUB_T, OUT_STUB_T>::write_hits()
{
    while (1)
    {
        wait();

        while (selected_stubs.num_available() > 0)
        {
            unsigned int i = 0;
            while ((i < max_stubs_per_cycle) && (selected_stubs.num_available() > 0))
            {
                data_valid.at(i).write(true);
                stub_outputs.at(i).write(selected_stubs.read());
                ++i;
            }

            wait(clk.posedge_event());

            data_valid.write(0);
            stub_outputs.write(output_stub_t());
        }
    }

}

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T>
void frontend_chip<IN_STUB_T, OUT_STUB_T>::prioritize_hits()
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
        // TODO: put this to log
        std::cerr << sc_time_stamp() << ": Front End Chip received more than "
                  << total_collected_stubs << " hits in " << collection_cycles
                  << " cycles." << std::endl;
    }
}
