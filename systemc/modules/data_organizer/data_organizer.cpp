/*!
 * @file data_organizer.cpp
 * @author Christian Amstutz
 * @date Apr 17, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#include "data_organizer.hpp"

// *****************************************************************************

/*!
 * @class data_organizer
 *
 * The module is sensitive to clk.pos and the change of the input_buffer.
 */

data_organizer::data_organizer(sc_module_name _name, unsigned int phi,
        unsigned int z) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        stream_in(NR_DETECTOR_LAYERS, "stream_in"),
        stub_out(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "stub_out"),
        clock_phase("clock_phase"),
        stub_table_sel("stub_table_sel"),
        time_stamp("time_stamp"),
        phi_sig("phi_sig"),
        z_sig("z_sig"),
        do_one_layer_map(NR_DETECTOR_LAYERS, "data_organizer_one_layer"),
        phi(phi),
        z(z)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(controller);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    phi_sig.write(phi);
    z_sig.write(z);

    // ----- Module instance / channel binding ---------------------------------
    unsigned int layer = 0;
    for (auto& one_do : do_one_layer_map)
    {
        one_do.clk.bind(clk);
        one_do.rst.bind(rst);
        one_do.time_stamp.bind(time_stamp);
        one_do.clock_phase.bind(clock_phase);
        one_do.stub_table_sel.bind(stub_table_sel);
        one_do.stream_in.bind(stream_in[layer]);
        auto output_iter = stub_out.begin_partial(layer, false, 0, true);
        one_do.stub_out.bind_by_iter(output_iter);
        one_do.phi.bind(phi_sig);
        one_do.z.bind(z_sig);

        ++layer;
    }

    return;
}

// *****************************************************************************
void data_organizer::controller()
{
	time_stamp.write(0);
	clock_phase.write(0);
    stub_table_sel.write(0);

    while (1)
    {
        wait();

        time_stamp.write(time_stamp.read()+1);

        sc_bv<DC_OUTPUT_WIDTH> new_word = stream_in[0].read();

        if ((clock_phase.read() == NR_DC_WINDOW_CYCLES-1) ||
                (new_word[DC_OUTPUT_WIDTH-1] == true))
        {
            clock_phase.write(0);
            if(stub_table_sel.read() == 0)
            {
                stub_table_sel.write(1);
            }
            else
            {
                stub_table_sel.write(0);
            }
        }
        else
        {
            clock_phase.write(clock_phase.read()+1);
        }
    }

}
