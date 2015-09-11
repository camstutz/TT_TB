/*!
 * @file processor_organizer_config.cpp
 * @author Christian Amstutz
 * @date September 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../common/input_collector_config.hpp"
#include "../common/time_demux_config.hpp"
#include "po_layer_splitter_config.hpp"

#include "../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class processor_organizer_config
{
    friend class processor_organizer;

private:
    unsigned int do_input_nr;
    unsigned int layer_nr;
    unsigned int processor_output_nr;

    unsigned int stub_buffer_in_FIFO_size;
    unsigned int stub_buffer_out_FIFO_size;
    unsigned int layer_splittet_FIFO_size;

public:
    input_collector_config input_collector;
    time_demux_config demultiplexer;
    po_layer_splitter_config layer_splitter;

    processor_organizer_config();

    void add_do();
    void set_do_input_nr(unsigned int input_nr);
    void set_layer_nr(unsigned int layer_nr);
    void set_processor_output_nr(unsigned int output_nr);
    void set_stub_buffer_in_FIFO_size(unsigned int stub_buffer_in_FIFO_size);
    void set_stub_buffer_out_FIFO_size(unsigned int stub_buffer_out_FIFO_size);
    void set_layer_splittet_FIFO_size(unsigned int layer_splittet_FIFO_size);

};
