/*!
 * @file hit_processor.cpp
 * @author Christian Amstutz
 * @date November 17, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_processor.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(hit_processor);
#endif

// *****************************************************************************

hit_processor::hit_processor(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        hit_input(LAYER_NUMBER, "hit_input"),
        am_superstrip_out(LAYER_NUMBER, "am_superstrip_out"),
        hitbuf_superstrip_out(LAYER_NUMBER, "hitbuf_superstrip_out"),
        hitbuf_substrip_out(LAYER_NUMBER, "hitbuf_substrip_out"),
        hit_processors(LAYER_NUMBER, "hit_processors")
{

//#ifdef MTI_SYSTEMC
//    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
//    do_stub_out_sig.register_signal_modelsim<do_out_data>();
//    fifo_stub_in.register_signal_modelsim<fm_out_data>();
//#endif

    unsigned int id = 0;
    sc_map_linear<hit_processor_one_layer>::iterator hit_proc_it = hit_processors.begin();
    for (; hit_proc_it != hit_processors.end(); ++hit_proc_it)
    {
        hit_proc_it->clk.bind(clk);
        hit_proc_it->hit_input(hit_input[id]);
        hit_proc_it->am_superstrip_out(am_superstrip_out[id]);
        hit_proc_it->hitbuf_superstrip_out(hitbuf_superstrip_out[id]);
        hit_proc_it->hitbuf_substrip_out(hitbuf_substrip_out[id]);

        ++id;
    }

    return;
}
