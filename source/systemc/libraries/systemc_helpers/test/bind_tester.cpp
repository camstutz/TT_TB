
#include "bind_tester.hpp"

//******************************************************************************
bind_tester::bind_tester(sc_module_name _name) :
        sc_module(_name),
        output(3, 2, "out_port")
{
    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void bind_tester::create_data()
{
    sc_map_square<sc_out<bool> >::square_iterator out_iter =
            output(0,2,0,1);

    wait(15, SC_NS);

    for(int i=0; i<6; ++i)
    {
        (*out_iter).write(true);
        ++out_iter;
        wait(10, SC_NS);
    }

    return;
}
