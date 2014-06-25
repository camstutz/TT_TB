/*!
 * @file hit_file.cpp
 * @author Christian Amstutz
 * @date June 25, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_file.hpp"

// *****************************************************************************
hit_file::hit_file() :
        file_ready_flag(false),
        new_line_processed(true),
        last_bunch_crossing(0)
{}

// *****************************************************************************
hit_file::~hit_file()
{
    file_handler.close();

    return;
}

// *****************************************************************************
bool hit_file::open(const std::string& filename)
{
    file_handler.open(filename.c_str(), std::ifstream::in);

    if (!file_handler)
    {
        std::cout << "Problem opening hit file " << filename << std::endl;
        return (false);
    }
    file_ready_flag = true;

    new_line = "";
    new_line_processed = true;
    last_bunch_crossing = 0;

    return(true);
}

// *****************************************************************************
void hit_file::close()
{
    file_ready_flag = false;
    file_handler.close();
}

// *****************************************************************************
bool hit_file::file_ready()
{
    return (file_ready_flag);
}

// *****************************************************************************
bool hit_file::data_ready()
{
    bool data_available;

    if (file_ready())
    {
        data_available = true;
    }
    else
    {
        data_available = !hit_buffer_even.empty() | !hit_buffer_odd.empty();
    }

    return (data_available);
}

// *****************************************************************************
bool hit_file::get_next_hit(hit*& return_hit)
{
    if ( hit_buffer_even.empty() & hit_buffer_odd.empty() )
    {
        read_file();
    }

    if (!hit_buffer_even.empty())
    {
        return_hit = hit_buffer_even.front();
        hit_buffer_even.pop();

        return (true);
    }

    if (!hit_buffer_odd.empty())
    {
        return_hit = hit_buffer_odd.front();
        hit_buffer_odd.pop();

        return (true);
    }

    return_hit = NULL;
    return (false);
}

// *****************************************************************************
void hit_file::write_old_format(const std::string& filename)
{
    std::ofstream output_file;
    output_file.open(filename.c_str(), std::ifstream::out);

    hit* new_hit;
    while(data_ready())
    {
        get_next_hit(new_hit);

        output_file << std::hex << std::setfill('0');
        output_file << std::setw(8) << new_hit->get_bunch_crossing();
        output_file << " ";
        output_file << std::setw(1) << new_hit->get_layer();
        output_file << " ";
        output_file << std::setw(1) << new_hit->get_phi();
        output_file << " ";
        output_file << std::setw(1) << new_hit->get_z();
        output_file << " ";
        output_file << std::setw(1) << new_hit->get_chip_number();
        output_file << " ";

        hit_value* new_hit_value = new_hit->get_value();

        output_file << std::setw(2) << new_hit_value->get_strip();
        output_file << " ";
        output_file << std::setw(2) << new_hit_value->get_bend();
        output_file << "\n";

        delete new_hit;
    }

    output_file.close();

    return;
}

// *****************************************************************************
void hit_file::read_file()
{
    unsigned int new_bunch_crossing = 0;

    while (hit_buffer_even.empty() & hit_buffer_odd.empty())
    {
        while(new_bunch_crossing <= (last_bunch_crossing+2))
        {
            if (new_line_processed)
            {
                std::getline(file_handler, new_line);
                new_line_processed = false;

                if (file_handler.eof())
                {
                    // process last line
                    parse_line(new_line);
                    new_line_processed = true;

                    close();
                    return;
                }
            }

            std::stringstream bx_check(new_line);
            bx_check >> new_bunch_crossing;

            if( bx_check.fail() )
            {
                new_line_processed = true;
                continue;
            }

            if ( new_bunch_crossing <= (last_bunch_crossing+2) )
            {
                parse_line(new_line);
                new_line_processed = true;
            }
        }
        last_bunch_crossing = new_bunch_crossing;
    }

    return;
}

// *****************************************************************************
bool hit_file::parse_line(const std::string& line)
{
    std::stringstream line_buffer(line);
    unsigned int bunch_crossing;
    unsigned int layer;
    unsigned int phi;
    unsigned int z;
    unsigned int chip_number;

    // Line starts with integer representing bunch crossing number
    line_buffer >> bunch_crossing;

    if( line_buffer.fail() )
    {
        return (false);
    }

    // any number of blank characters
    while (line_buffer.peek() == ' ')
    {
        line_buffer.get();
    }

    // next character must be a '/'
    if (line_buffer.get() != '/')
    {
        return (false);
    }

    // any number of blank characters
    while (line_buffer.peek() == ' ')
    {
        line_buffer.get();
    }

    // check validity of address
    std::string address;
    std::getline(line_buffer, address, ' ');
    unsigned int address_length = address.length();
    if ( line_buffer.eof()                     |
         (address_length < address_length_min) |
         (address_length > address_length_max)  )
    {
        return (false);
    }

    // todo: check for if there are only numbers in address

    unsigned int layer_comp;

    if (address_length != address_length_min)
    {
        layer_comp = address_length_max - address_length;
    }
    else
    {
        layer_comp = 0;
    }

    std::stringstream layer_stream;
    layer_stream << address.substr(layer_pos, phi_pos-layer_pos+layer_comp);
    layer_stream >> layer;

    std::stringstream phi_stream;
    phi_stream << address.substr(phi_pos+layer_comp, z_pos-phi_pos);
    phi_stream >> phi;

    std::stringstream z_stream;
    z_stream << address.substr(z_pos+layer_comp, chip_number_pos-z_pos);
    z_stream >> z;

    std::stringstream chip_stream;
    chip_stream << address.substr(chip_number_pos+layer_comp, address_length_min-chip_number_pos);
    chip_stream >> chip_number;

    // any number of blank characters
    while (line_buffer.peek() == ' ')
    {
        line_buffer.get();
    }

    // next character must be a '-'
    if (line_buffer.get() != '-')
    {
        return (false);
    }

    // next character must be a '>'
    if (line_buffer.get() != '>')
    {
        return(false);
    }

    // any number of blank characters
    while (line_buffer.peek() == ' ')
    {
        line_buffer.get();
    }

    // decode value from file
    const unsigned int cbc_value_length = hit_value_cbc::binary_value_length;
    const unsigned int max_nr_cbc_values = 3;
    const unsigned int mpa_value_length = hit_value_mpa::binary_value_length;
    const unsigned int max_nr_mpa_values = 4;
    std::string total_value;
    line_buffer >> total_value;

    // todo: remove trailing spaces
    // todo: check if value is binary, contains only 0s and 1s

    // Create CBC hits
    if ( ((total_value.length() % cbc_value_length) == 0)
            & ((total_value.length() / cbc_value_length) <= max_nr_cbc_values) )
    {
        for(int i=1; i*cbc_value_length <= total_value.length(); ++i)
        {
            std::string value_string;
            value_string = total_value.substr((i-1)*cbc_value_length, cbc_value_length);

            hit_value* value_p = new hit_value_cbc(value_string);
            hit* hit_p = new hit(bunch_crossing, layer, phi, z, chip_number, value_p);

            if ( (bunch_crossing % 2) == 0)
            {
                hit_buffer_even.push(hit_p);
            }
            else
            {
                hit_buffer_odd.push(hit_p);
            }
        }
    }
    // Create MPA hits
    else if( ((total_value.length() % mpa_value_length) == 0)
            & ((total_value.length() / mpa_value_length) <= max_nr_mpa_values) )
    {
        for(unsigned int i=1; i*mpa_value_length <= total_value.length(); ++i)
        {
            std::string value_string;
            value_string = total_value.substr((i-1)*mpa_value_length, mpa_value_length);

            hit_value* value_p = new hit_value_mpa(value_string);
            hit* hit_p = new hit(bunch_crossing, layer, phi, z, chip_number, value_p);

            if (i < 3)
            {
                hit_buffer_even.push(hit_p);
            }
            else
            {
                hit_buffer_odd.push(hit_p);
            }
        }
    }
    else
    {
        return (false);
    }


    return (true);
}
