/*!
 * @file pattern_memory.cpp
 * @author Christian Amstutz
 * @date November 18, 2014
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

    initialize_patterns();

    return;
}

// *****************************************************************************
void pattern_memory::lookup_road()
{
	while (1)
	{
		wait();

		pattern_bank_t::iterator found_entry = pattern_bank.find(road_input.read());
		if (found_entry != pattern_bank.end())
		{
			for(unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
			{
				pattern_t found_pattern = found_entry->second;
				superstrip_outputs[layer].write(found_pattern[layer]);
			}
		}
	}

}

// *****************************************************************************
void pattern_memory::initialize_patterns()
{
	for (road_t pat_nr=0; pat_nr<AM_CHIP_PATTERN_NR; ++pat_nr)
    {
		pattern_t pattern;
		pattern.resize(LAYER_NUMBER);

		for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
		{
			pattern[layer] = pat_nr;
		}

		pattern_bank.insert(std::pair<road_t, pattern_t>(pat_nr, pattern));
    }

    return;
}

// *****************************************************************************
void pattern_memory::print_pattern_bank()
{
	std::cout << std::endl << "Pattern Bank:" << std::endl;

	pattern_bank_t::iterator pattern_it = pattern_bank.begin();
	for (; pattern_it != pattern_bank.end(); ++pattern_it)
	{
		std::cout << pattern_it->first << ": ";
		for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
		{
			 std::cout << pattern_it->second[layer] << ", ";
		}
		std::cout << std::endl;
	}

	return;
}
