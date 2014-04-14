/*!
 * @file main_fsm.cpp
 * @author Christian Amstutz
 * @date Apr 15, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "main_fsm.hpp"

// *****************************************************************************

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
        init("init"),
        pok(NR_DETECTOR_LAYERS, "pok"),
        hee_reg(NR_DETECTOR_LAYERS, "hee_reg"),
        finish_road("finish_road"),
        pop(NR_DETECTOR_LAYERS, "pop"),
        en(NR_DETECTOR_LAYERS, "en"),
        select_iam("selec_iam"),
        init_ev("init_ev"),
        state("state")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(fsm);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    state = RESET;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void main_fsm::fsm()
{
    while (1)
    {
        wait();

        unsigned int id;
        unsigned int AM_latency_cnt;

        switch (state)
        {
        case RESET:
            state = RX_HIT;
            break;

        case RX_HIT:
            id = 0;
            for (auto& hee_reg_single : hee_reg)
            {
                pop[id] = !hee_reg_single;
                en[id] = !hee_reg_single & pok[id];

                ++id;
            }

            for (auto& hee_reg_single : hee_reg)
            {
                if (hee_reg_single == false)
                {
                    state = WAIT_T0;
                    AM_latency_cnt = am_latency;
                    break;
                }
            }
            state = RX_HIT;
            break;

        case WAIT_T0:
            pop.write_all(false);
            en.write_all(false);

            if (AM_latency_cnt == 0)
            {
                state = SEND_ROAD;
            }
            else
            {
                --AM_latency_cnt;
                state = WAIT_T0;
            }
            break;

        case SEND_ROAD:
            pop.write_all(false);
            en.write_all(false);

            if (finish_road == true)
            {
                state = SEND_INIT_EVENT;
            }
            else
            {
                state = SEND_ROAD;
            }
            break;

        case SEND_INIT_EVENT:
            pop.write_all(false);
            en.write_all(false);
            init_ev = 7;

            state = RX_HIT;
            break;

        default:
            state = RESET;
        }
    }
}
