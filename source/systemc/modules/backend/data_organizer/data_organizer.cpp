/*!
 * @file data_organizer.cpp
 * @author Christian Amstutz
 * @date July 31, 2014
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
        dv(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "dv"),
        stub_out(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "stub_out"),
        clock_phase("clock_phase"),
        stub_table_sel("stub_table_sel"),
        time_stamp("time_stamp"),
        phi_sig("phi_sig"),
        z_sig("z_sig"),
        do_one_layer_map_mpa(NR_DETECTOR_MPA_LAYERS, "data_organizer_one_layer_mpa"),
        do_one_layer_map_cbc(NR_DETECTOR_CBC_LAYERS, "data_organizer_one_layer_cbc"),
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
    sc_map_linear<data_organizer_one_layer_mpa>::iterator do_mpa_it = do_one_layer_map_mpa.begin();
    for (; do_mpa_it != do_one_layer_map_mpa.end(); ++do_mpa_it)
    {
        do_mpa_it->clk.bind(clk);
        do_mpa_it->rst.bind(rst);
        do_mpa_it->time_stamp.bind(time_stamp);
        do_mpa_it->clock_phase.bind(clock_phase);
        do_mpa_it->stub_table_sel.bind(stub_table_sel);
        do_mpa_it->stream_in.bind(stream_in[layer]);
        sc_map_square<sc_out<bool> >::square_iterator dv_iter = dv.begin_partial(layer, false, 0, true);
        do_mpa_it->dv.bind_by_iter(dv_iter);
        sc_map_square<sc_out<data_organizer_one_layer::do_stub_t> >::square_iterator output_iter = stub_out.begin_partial(layer, false, 0, true);
        do_mpa_it->stub_out.bind_by_iter(output_iter);
        do_mpa_it->phi.bind(phi_sig);
        do_mpa_it->z.bind(z_sig);

        ++layer;
    }

    layer = NR_DETECTOR_MPA_LAYERS;
    sc_map_linear<data_organizer_one_layer_cbc>::iterator do_cbc_it = do_one_layer_map_cbc.begin();
    for (; do_cbc_it != do_one_layer_map_cbc.end(); ++do_cbc_it)
    {
        do_cbc_it->clk.bind(clk);
        do_cbc_it->rst.bind(rst);
        do_cbc_it->time_stamp.bind(time_stamp);
        do_cbc_it->clock_phase.bind(clock_phase);
        do_cbc_it->stub_table_sel.bind(stub_table_sel);
        do_cbc_it->stream_in.bind(stream_in[layer]);
        sc_map_square<sc_out<bool> >::square_iterator dv_iter = dv.begin_partial(layer, false, 0, true);
        do_cbc_it->dv.bind_by_iter(dv_iter);
        sc_map_square<sc_out<data_organizer_one_layer::do_stub_t> >::square_iterator output_iter = stub_out.begin_partial(layer, false, 0, true);
        do_cbc_it->stub_out.bind_by_iter(output_iter);
        do_cbc_it->phi.bind(phi_sig);
        do_cbc_it->z.bind(z_sig);

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

        do_in_t new_word = stream_in[0].read();

        if ((clock_phase.read() == NR_DC_WINDOW_CYCLES-1) ||
                ((new_word.get_header() & 0x2) == true))
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
