/*!
 * @file pattern_memory.cpp
 * @author Christian Amstutz
 * @date March 30, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "pattern_memory.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(pattern_memory);
#endif

// *****************************************************************************

pattern_memory::pattern_memory(const sc_module_name _name, pattern_bank *p_bank) :
        sc_module(_name),
        clk("clk"),
        road_input("road_input"),
        superstrip_outputs(LAYER_NUMBER, "superstrip_outputs"),
		superstrip_outputs_sig(LAYER_NUMBER, "superstrip_outputs_sig"),
		delay_superstrip_outputs(LAYER_NUMBER, "delay_superstrip_outputs"),
        patterns(p_bank)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(lookup_road);
        sensitive << road_input;

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

//#ifdef MTI_SYSTEMC
//    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
//    do_stub_out_sig.register_signal_modelsim<do_out_data>();
//    fifo_stub_in.register_signal_modelsim<fm_out_data>();
//#endif

    sc_map_linear<sc_delay_signal<superstrip_t, PATTERN_MEMORY_LATENCY> >::iterator delay_superstrip_output_it = delay_superstrip_outputs.begin();
    sc_map_linear<sc_signal<superstrip_t> >::iterator superstrip_output_sig_it = superstrip_outputs_sig.begin();
	sc_map_linear<sc_out<superstrip_t> >::iterator superstrip_output_it = superstrip_outputs.begin();
	for (; delay_superstrip_output_it != delay_superstrip_outputs.end(); ++delay_superstrip_output_it)
	{
		delay_superstrip_output_it->clk.bind(clk);
		delay_superstrip_output_it->input.bind(*superstrip_output_sig_it);
		delay_superstrip_output_it->delayed.bind(*superstrip_output_it);

		++superstrip_output_sig_it;
		++superstrip_output_it;
	}

    return;
}

// *****************************************************************************
void pattern_memory::lookup_road()
{
	while (1)
	{
		wait();

		std::pair<bool, pattern_bank::pattern_t> pattern= patterns->find_pattern(road_input.read());

		if (pattern.first)
		{
			for(unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
			{
				superstrip_outputs_sig[layer].write(pattern.second[layer]);
			}
		}
	}

}

// *****************************************************************************
void pattern_memory::print_pattern_bank()
{
	std::cout << std::endl << "Pattern Bank:" << std::endl;
	patterns->print_pattern_bank();

	return;
}
