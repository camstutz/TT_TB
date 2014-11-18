/*!
 * @file hit_processor_one_layer.cpp
 * @author Christian Amstutz
 * @date November 17, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_processor_one_layer.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(hit_processor);
#endif

// *****************************************************************************

hit_processor_one_layer::hit_processor_one_layer(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        hit_input("hit_input"),
        am_superstrip_out("superstrip_out"),
        hitbuf_superstrip_out("superstrip_out"),
        hitbuf_substrip_out("substrip_out")
{

//#ifdef MTI_SYSTEMC
//    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
//    do_stub_out_sig.register_signal_modelsim<do_out_data>();
//    fifo_stub_in.register_signal_modelsim<fm_out_data>();
//#endif

    SC_THREAD(write_outputs);
        sensitive << hit_input;

    return;
}

// *****************************************************************************
void hit_processor_one_layer::write_outputs()
{
    am_superstrip_out.write(IDLE_EVENT);
    hitbuf_superstrip_out.write(IDLE_EVENT);

    while(1)
    {
        wait();

        if (hit_input.read() == IDLE_EVENT)
        {
            am_superstrip_out.write(IDLE_EVENT);
            hitbuf_superstrip_out.write(IDLE_EVENT);
        }
        else if (hit_input.read() == START_EVENT)
        {
            am_superstrip_out.write(START_EVENT);
            hitbuf_superstrip_out.write(START_EVENT);
        }
        else {
            am_superstrip_out.write(generate_superstrip(hit_input.read()));
            hitbuf_superstrip_out.write(generate_superstrip(hit_input.read()));
            hitbuf_substrip_out.write(generate_substrip(hit_input.read()));
        }

    }
}

// *****************************************************************************
superstrip_t hit_processor_one_layer::generate_superstrip(hit_t hit)
{
    return (hit >> SS_BIT_WIDTH);
}

// *****************************************************************************
substrip_t hit_processor_one_layer::generate_substrip(hit_t hit)
{
    superstrip_t mask = 0x0;
    for(unsigned int i=0; i<SS_BIT_WIDTH; ++i)
    {
        mask = mask | (0x01 << i);
    }

    return (hit & mask);
}
