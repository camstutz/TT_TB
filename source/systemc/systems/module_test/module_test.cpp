
#include "module_test.hpp"

// *****************************************************************************
module_test::module_test(const sc_module_name _name, const std::vector<sensor_module_config>& configuration) :
        sc_module(_name),
        clock("clock"),
        sensor_modules_test(10, "test_modules", configuration),
        hit_fifos_test(16, "hit_fifo_test"),
        gbt_links_test(1, "gbt_test")
{

    for (sc_map_linear<sensor_module>::iterator module_it = sensor_modules_test.begin();
         module_it != sensor_modules_test.end();
         ++module_it)
    {
        module_it->clk.bind(clock);
        module_it->stub_inputs.bind(hit_fifos_test);
        module_it->gbt_link.bind(gbt_links_test[0]);
    }

    return;
}
