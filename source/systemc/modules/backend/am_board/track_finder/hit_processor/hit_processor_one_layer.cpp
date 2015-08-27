/*!
 * @file hit_processor_one_layer.cpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "hit_processor_one_layer.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(hit_processor);
#endif

// *****************************************************************************

hit_processor_one_layer::hit_processor_one_layer(const sc_module_name _name,
        const hit_processor_one_layer_config& configuration) :
        sc_module(_name),
        configuration(configuration),
        clk("clk"),
        hit_input("hit_input"),
        am_superstrip_out("am_superstrip_out"),
        hitbuf_superstrip_out("hitbuf_superstrip_out"),
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
    am_superstrip_out.write(superstrip_stream::IDLE);
    hitbuf_superstrip_out.write(superstrip_stream::IDLE);

    while(1)
    {
        wait();

        hit_stream hit = hit_input.read();
        if (hit.is_opcode())
        {
            am_superstrip_out.write(hit);
            hitbuf_superstrip_out.write(hit);
        }
        else
        {
            am_superstrip_out.write(generate_superstrip(hit.get_value()));
            hitbuf_superstrip_out.write(generate_superstrip(hit.get_value()));
            hitbuf_substrip_out.write(generate_substrip(hit.get_value()));
        }

    }
}

// *****************************************************************************
superstrip_t hit_processor_one_layer::generate_superstrip(hit_t hit)
{
    return (hit >> configuration.SS_width_bits);
}

// *****************************************************************************
substrip_t hit_processor_one_layer::generate_substrip(hit_t hit)
{
    superstrip_t mask = 0x0;
    for(unsigned int i=0; i<configuration.SS_width_bits; ++i)
    {
        mask = mask | (0x01 << i);
    }

    return (hit & mask);
}
