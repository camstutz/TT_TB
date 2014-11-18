/*!
 * @file road_processor.cpp
 * @author Christian Amstutz
 * @date Nov 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "road_processor.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(road_processor);
#endif

// *****************************************************************************

road_processor::road_processor(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        road_input("road_input"),
        road_lookup("road_lookup"),
        found_pattern(LAYER_NUMBER, "found_pattern"),
        superstrip_lookup(LAYER_NUMBER, "superstrip_lookup"),
        hit_lookup_result(LAYER_NUMBER, "hit_lookup_result"),
        hit_output(LAYER_NUMBER, "hit_output")
{

//#ifdef MTI_SYSTEMC
//    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
//    do_stub_out_sig.register_signal_modelsim<do_out_data>();
//    fifo_stub_in.register_signal_modelsim<fm_out_data>();
//#endif

    return;
}
