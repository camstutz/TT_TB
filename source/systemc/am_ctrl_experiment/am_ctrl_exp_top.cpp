/* !
 * @file am_ctrl_exp_top.cpp
 * @author Christian Amstutz
 * @date December 3, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_ctrl_exp_top.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(am_ctrl_exp_top);
#endif

// *****************************************************************************

const std::string am_ctrl_exp_top::in_filename = "ss.txt";
const std::string am_ctrl_exp_top::out_filename = "ss_out.txt";
const unsigned int output_width = 4;

// *****************************************************************************

am_ctrl_exp_top::am_ctrl_exp_top(const sc_module_name _name) :
        sc_module(_name),
        clock("clock", AMEXP_CLOCK_PERIOD_NS, SC_NS, 0.5, 10, SC_NS, true),
        input_hit_sig(LAYER_NUMBER, "input_hit_sig"),
        output_hit_sig(LAYER_NUMBER, "output_hit_sig"),
        am_board("AM_board")
{
    am_board.clk.bind(clock);
    am_board.hit_input.bind(input_hit_sig);
    am_board.hit_output.bind(output_hit_sig);

    SC_THREAD(generate_input);
    SC_THREAD(log_input);
        input_hit_sig.make_sensitive(sensitive);
    SC_THREAD(log_result);
        output_hit_sig.make_sensitive(sensitive);

    read_hitfile();

    return;
}

// *****************************************************************************
am_ctrl_exp_top::~am_ctrl_exp_top()
{
    std::cout << in_log_buffer.str();
    std::cout << out_log_buffer.str();

    in_file.close();
    out_file.close();

    return;
}

// *****************************************************************************
void am_ctrl_exp_top::generate_input()
{
    unsigned int current_event_nr = 0xFFFFFFFF;
    input_hit_sig.write_all(hit_stream::IDLE);

    while (!hit_queue.empty())
    {
        hitfile_line hitline = hit_queue.front();
        hit_queue.pop();

        if (hitline.hits[0].data.event != current_event_nr)
        {
            sc_time wait_time;
            wait_time = ((hitline.timestamp-1) * sc_time(AMEXP_CLOCK_PERIOD_NS, SC_NS));
            wait_time = wait_time - sc_time_stamp();

            input_hit_sig.write_all(hit_stream::IDLE);
            if (wait_time > sc_time(0, SC_PS))
            {
                wait(wait_time);
            }

            input_hit_sig.write_all(hit_stream::START_WORD);
            wait(AMEXP_CLOCK_PERIOD_NS, SC_NS);

            current_event_nr = hitline.hits[0].data.event;
        }

        sc_time wait_time;
        wait_time = (hitline.timestamp * sc_time(AMEXP_CLOCK_PERIOD_NS, SC_NS));
        wait_time = wait_time - sc_time_stamp();
        if (wait_time > sc_time(0, SC_PS))
        {
            wait(wait_time);
        }

        for(unsigned int layer=0; layer<LAYER_NUMBER; ++layer)
        {
            if (hitline.hits[layer].dv)
            {
                hit_t new_hit = (hitline.hits[layer].data.superstrip << 8) | hitline.hits[layer].data.stub;
                input_hit_sig[layer].write(new_hit);
            }
            else
            {
                input_hit_sig[layer].write(hit_stream::IDLE);
            }
        }
        wait(AMEXP_CLOCK_PERIOD_NS, SC_NS);
    }

    return;
}

// *****************************************************************************
void am_ctrl_exp_top::log_input()
{
    in_log_buffer << std::endl
                  << "Simulation Input of AM experiment:" << std::endl
                  << "**********************************" << std::endl;

    while(1)
    {
        wait();

        in_log_buffer << sc_time_stamp() << ": ";
        for(unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            in_log_buffer << std::hex << input_hit_sig[layer].read() << ", ";
        }
        in_log_buffer << std::endl;
    }
}

// *****************************************************************************
void am_ctrl_exp_top::log_result()
{
    out_log_buffer << std::endl
                   << "Simulation Output of AM experiment:" << std::endl
                   << "***********************************" << std::endl;

    out_file.open(out_filename.c_str());

    while(1)
    {
        wait();

        out_log_buffer << sc_time_stamp() << ": ";

        bool value_availble = false;
        std::stringstream file_line("");

        for(unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            hit_stream read_hit = am_board.hit_output[layer].read();

            out_log_buffer << std::hex << read_hit << ", ";

            if (read_hit.is_opcode())
            {
                hit_stream empty_hit;
                file_line << "0 ";
                file_line << std::setfill('0') << std::setw(4) << std::hex;
                file_line << empty_hit.get_value() << " ";
            }
            else
            {
                file_line << "1 ";
                file_line << std::setfill('0') << std::setw(4) << std::hex;
                file_line << read_hit.get_value() << " ";
                value_availble = true;
            }
        }
        out_log_buffer << std::endl;

        if (value_availble)
        {
            out_file << file_line.rdbuf() << std::endl;
        }
    }
}

// *****************************************************************************
void am_ctrl_exp_top::read_hitfile()
{
    in_file.open(in_filename.c_str());
    if (in_file.is_open())
    {
        std::string fileLine;
        while (std::getline(in_file,fileLine))
        {
            if(fileLine != "")
            {
                std::stringstream fileLineStream(fileLine);
                hitfile_line formated_line;
                formated_line.hits.resize(LAYER_NUMBER);

                fileLineStream >> std::hex >> formated_line.timestamp;
                for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
                {
                    fileLineStream >> std::hex >> formated_line.hits[layer].dv;

                    unsigned int data;
                    fileLineStream >> std::hex >> data;
                    formated_line.hits[layer].data.event = (data & 0xFF000000) >> 24;
                    formated_line.hits[layer].data.layer = (data & 0x00FF0000) >> 16;
                    formated_line.hits[layer].data.superstrip = (data & 0x0000FF00) >> 8;
                    formated_line.hits[layer].data.stub = (data & 0x000000FF);
                }

//                std::cout << std::hex << formated_line.timestamp <<
//                        " " << formated_line.hits[0].dv << " " << formated_line.hits[0].data.event << "," << formated_line.hits[0].data.layer << "," << formated_line.hits[0].data.superstrip << "," << formated_line.hits[0].data.stub <<
//                        " " << formated_line.hits[1].dv << " " << formated_line.hits[1].data.event << "," << formated_line.hits[1].data.layer << "," << formated_line.hits[1].data.superstrip << "," << formated_line.hits[1].data.stub <<
//                        std::endl;

                hit_queue.push(formated_line);
            }
        }
    }
    else
    {
        std::cout << "Input file could not be read: " << in_file << std::endl;
    }

    return;
}
