/*!
 * @file main_fsm.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "main_fsm.hpp"

// *****************************************************************************
const unsigned int main_fsm::am_latency = 18;
const main_fsm::fsm_states main_fsm::RESET = 0x01;
const main_fsm::fsm_states main_fsm::RX_HIT = 0x02;
const main_fsm::fsm_states main_fsm::WAIT_T0 = 0x03;
const main_fsm::fsm_states main_fsm::SEND_ROAD = 0x04;
const main_fsm::fsm_states main_fsm::SEND_INIT_EVENT = 0x05;

// *****************************************************************************

/*!
 * @class main_fsm
 *
 * The module is sensitive to clk.pos().
 */

main_fsm::main_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        pok(NR_DETECTOR_LAYERS, "pok"),
        hee_reg(NR_DETECTOR_LAYERS, "hee_reg"),
        hee_reg_before(NR_DETECTOR_LAYERS, "hee_reg_before"),
        finish_road("finish_road"),
        pop(NR_DETECTOR_LAYERS, "pop"),
        en(NR_DETECTOR_LAYERS, "en"),
        init_ev("init_ev"),
        current_state("current_state"),
        next_state("next_state")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(state_logic);
        sensitive << clk.pos();
    SC_THREAD(combinatorial);
        sensitive << current_state << finish_road << AM_latency_cnt;
        pok.make_sensitive(this->sensitive);
        hee_reg.make_sensitive(this->sensitive);

    // ----- Module channel/variable initialization ----------------------------
    current_state = RESET;
    next_state = RX_HIT;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void main_fsm::state_logic()
{
    while (1)
    {
        wait();

        current_state.write(next_state.read());

        if (current_state == WAIT_T0)
        {
            AM_latency_cnt.write(AM_latency_cnt.read()-1);
        }
        else
        {
            AM_latency_cnt.write(am_latency);
        }
    }

}

// *****************************************************************************
void main_fsm::combinatorial()
{
    while (1)
    {
        unsigned int id;
        bool all_hee_reg;
        sc_map_linear<sc_in<bool> >::iterator hee_reg_it = hee_reg.begin();

        switch (current_state)
        {
        case RESET:
            init_ev = 0;
            next_state.write(RX_HIT);
            break;

        case RX_HIT:
            init_ev = 0;

            id = 0;
            hee_reg_it = hee_reg.begin();
            for (; hee_reg_it != hee_reg.end(); ++hee_reg_it)
            {
                pop[id] = !hee_reg_it->read();
                en[id] = !hee_reg_it->read() & pok[id].read();
                ++id;
            }

            all_hee_reg = true;
            hee_reg_it = hee_reg.begin();
            for (; hee_reg_it != hee_reg.end(); ++hee_reg_it)
            {
                if (hee_reg_it->read() == false)
                {
                    all_hee_reg = false;
                }
            }

            if (all_hee_reg)
            {
                next_state = WAIT_T0;
            }
            else
            {
                next_state = RX_HIT;
            }
            break;

        case WAIT_T0:
            pop.write_all(false);
            en.write_all(false);
            init_ev = 0;

            if (AM_latency_cnt.read() == 0)
            {
                next_state = SEND_ROAD;
            }
            else
            {
                next_state = WAIT_T0;
            }
            break;

        case SEND_ROAD:
            pop.write_all(false);
            en.write_all(false);
            init_ev = 0;

            if (finish_road == false)
            {
                next_state = SEND_INIT_EVENT;
            }
            else
            {
                next_state = SEND_ROAD;
            }
            break;

        case SEND_INIT_EVENT:
            pop.write_all(false);
            en.write_all(false);
            init_ev = 7;

            next_state = RX_HIT;
            break;

        default:
            next_state = RESET;
        }

        wait();
    }

}
