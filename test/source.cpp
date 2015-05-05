
#include "source.hpp"

//******************************************************************************
source::source(sc_module_name _name) :
        sc_module(_name),
        output(2, "out_port") {

    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void source::create_data() {

    wait(15, SC_NS);

    output(0,1) = true;

    wait(85, SC_NS);

    output[0].write(false);

    wait(100, SC_NS);

    output.at(0).write(true);
    output.at(1).write(false);

    wait(100, SC_NS);

    output.at(0).write(false);

    return;
}

//******************************************************************************
source_square::source_square(sc_module_name _name) :
        sc_module(_name),
        output(3, 2, "out_port") {

    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void source_square::create_data() {

    wait(15, SC_NS);

    output.at(0,0).write(true);
    output.at(0,1).write(true);
    output.at(1,0).write(true);

    wait(85, SC_NS);

    output.at(1,1).write(true);
    output.at(2,0).write(true);
    output.at(2,1).write(true);

    wait(100, SC_NS);

    output.at(0,0).write(false);
    output.at(0,1).write(false);
    output.at(1,0).write(false);

    wait(100, SC_NS);

    output.at(1,1).write(false);
    output.at(2,0).write(false);
    output.at(2,1).write(false);

    wait(100, SC_NS);

    output.at(0,1).write(true);
    output.at(1,1).write(false);
    output.at(0,0).write(true);

    wait(100, SC_NS);

    output.at(0,0).write(false);
    output.at(1,1).write(true);
    output.at(2,1).write(true);

    wait(100, SC_NS);

    output.at(1,1).write(true);
    output.at(1,0).write(true);
    output.at(2,0).write(true);

    wait(100, SC_NS);

    return;
}

//******************************************************************************
source_cube::source_cube(sc_module_name _name) :
        sc_module(_name),
        output(4, 3, 2, "out_port") {

    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void source_cube::create_data() {

    wait(15, SC_NS);

    output.at(0,0,0).write(true);
    output.at(1,0,0).write(true);
    output.at(3,0,1).write(true);
    output.at(2,1,0).write(true);

    wait(85, SC_NS);

    output.at(0,0,1).write(true);
    output.at(1,0,0).write(true);
    output.at(3,0,1).write(true);
    output.at(2,1,0).write(true);

    wait(100, SC_NS);

    output.at(0,1,0).write(true);
    output.at(1,0,0).write(true);
    output.at(3,1,1).write(true);
    output.at(2,1,0).write(true);

    wait(100, SC_NS);

    output.at(0,1,1).write(true);
    output.at(1,0,0).write(true);
    output.at(3,2,1).write(true);
    output.at(2,2,0).write(true);

    wait(100, SC_NS);

    output.at(0,2,0).write(true);
    output.at(1,0,0).write(true);
    output.at(3,0,1).write(true);
    output.at(2,1,0).write(true);

    wait(100, SC_NS);

    output.at(0,0,0).write(true);
    output.at(1,2,0).write(true);
    output.at(3,0,1).write(true);
    output.at(3,2,1).write(true);

    wait(100, SC_NS);

    output.at(0,1,0).write(true);
    output.at(1,2,0).write(true);
    output.at(3,0,1).write(true);
    output.at(2,1,0).write(true);

    wait(100, SC_NS);

    return;
}

//******************************************************************************
source_4d::source_4d(sc_module_name _name) :
        sc_module(_name),
        output(5, 4, 3, 2, "out_port") {

    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void source_4d::create_data() {

    wait(15, SC_NS);

    output.at(0,0,0,0).write(true);
    output.at(0,0,0,1).write(true);
    output.at(0,1,0,0).write(true);
    output.at(4,3,2,1).write(true);

    wait(85, SC_NS);

    output.at(1,0,0,0).write(true);
    output.at(2,0,0,1).write(true);
    output.at(2,1,0,0).write(true);
    output.at(2,3,2,1).write(true);

    wait(100, SC_NS);

    output.at(3,0,0,0).write(true);
    output.at(2,0,0,1).write(true);
    output.at(1,1,0,0).write(true);
    output.at(1,3,2,1).write(true);

    wait(100, SC_NS);

    output.at(2,0,1,0).write(true);
    output.at(2,0,1,1).write(true);
    output.at(2,1,1,0).write(true);
    output.at(2,3,1,1).write(true);

    wait(100, SC_NS);

    output.at(1,0,0,0).write(true);
    output.at(0,0,1,1).write(true);
    output.at(0,2,0,0).write(true);
    output.at(4,1,2,1).write(true);

    wait(100, SC_NS);

    output.at(0,1,2,0).write(true);
    output.at(0,0,0,1).write(true);
    output.at(0,3,0,0).write(true);
    output.at(1,1,2,1).write(true);

    wait(100, SC_NS);

    output.at(0,1,0,1).write(true);
    output.at(0,2,0,0).write(true);
    output.at(3,1,0,0).write(true);
    output.at(4,0,2,0).write(true);

    wait(100, SC_NS);

    return;
}
