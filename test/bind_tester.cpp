
#include "bind_tester.hpp"

//******************************************************************************
bind_tester::bind_tester(sc_module_name _name) :
        sc_module(_name),
        output(3, 2, "out_port") {

    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void bind_tester::create_data() {

    auto out_iter = output.begin_dim(0,2,true, 0,1,true);

    wait(15, SC_NS);

    for(int i=0; i<6; ++i)
    {
        (*out_iter).write(true);
        ++out_iter;
        wait(10, SC_NS);
    }

    return;
}
