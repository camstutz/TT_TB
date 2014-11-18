/*!
 * @file pattern_memory.cpp
 * @author Christian Amstutz
 * @date Nov 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "pattern_memory.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(pattern_memory);
#endif

// *****************************************************************************

pattern_memory::pattern_memory(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        road_input("road_input"),
        superstrip_outputs(LAYER_NUMBER, "superstrip_outputs")
{

//#ifdef MTI_SYSTEMC
//    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
//    do_stub_out_sig.register_signal_modelsim<do_out_data>();
//    fifo_stub_in.register_signal_modelsim<fm_out_data>();
//#endif

    return;
}
