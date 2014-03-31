/*!
 * @file am_board.cpp
 * @author Christian Amstutz
 * @date Apr 3, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_board.hpp"

// *****************************************************************************

/*!
 * @class am_board
 *
 * The module is sensitive to ...
 */

am_board::am_board(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        init_ev("init_ev"),
        write_en(NR_DETECTOR_LAYERS, "write_en"),
        pattern_inputs(NR_DETECTOR_LAYERS, "pattern_input"),
        data_ready("data_ready"),
        road_output("road_output")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_stubs);
        sensitive << clk.pos();
    SC_THREAD(detect_roads);
    SC_THREAD(write_roads);

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------


    initialize_patterns();

    return;
}

// *****************************************************************************
void am_board::process_incoming_stubs()
{
    while(1)
    {
        wait();

        for (unsigned int layer = 0; layer < NR_DETECTOR_LAYERS; ++layer)
        {
            pattern_t pattern = pattern_inputs[layer].read();
            if (write_en[layer])
            {
                auto road_addresses = pattern_bank[layer].equal_range(pattern.to_uint());
                auto road_addr_it = road_addresses.first;
                while (road_addr_it != road_addresses.second)
                {
                    auto road_addr = road_addr_it->second.to_uint();
                    match_table[road_addr][layer] = true;
                    ++road_addr_it;
                }
            }
        }
    }

}

// *****************************************************************************
void am_board::detect_roads()
{
    // Prepare the pattern which represents a detected road in the match_table
    std::array<bool, NR_DETECTOR_LAYERS> road_detect_pattern;
    for(auto& position : road_detect_pattern)
    {
        position = true;
    }

    while (1)
    {
        wait();

        unsigned road_nr = 0;
        for (auto match_line : match_table)
        {
            if(match_line == road_detect_pattern)
            {
                detected_roads_buffer.write(road_addr_t(road_nr));
            }
            ++road_nr;
        }
    }

}

// *****************************************************************************
void am_board::write_roads()
{
    while (1)
    {
        wait();

        road_addr_t road;
        bool road_available = detected_roads_buffer.nb_read(road);
        if (road_available)
        {
            road_output.write(road);
        }
    }
}

// *****************************************************************************
void am_board::initialize_patterns()
{
    for (auto& pattern_bank_layer: pattern_bank)
    {
        for (unsigned int pat_nr=0; pat_nr<nr_pattern; ++pat_nr)
        {
            pattern_t pattern;
            pattern = ( (sc_bv<2>(0), sc_bv<4>(0), sc_bv<4>(0), sc_bv<8>(pat_nr)) );
            pattern_bank_layer.emplace(pattern.to_uint(), pat_nr);
        }
    }
}
