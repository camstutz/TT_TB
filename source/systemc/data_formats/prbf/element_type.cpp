/*!
 * @file prbf_element_type.cpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "element_type.hpp"

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************

const element_type element_type::sof = element_type(element_type::local, 2, element_type::MPA);
const element_type element_type::eof = element_type(element_type::local, 1, element_type::MPA);
const element_type element_type::local_CBC = element_type(element_type::local, 0, element_type::CBC);
const element_type element_type::local_MPA = element_type(element_type::local, 0, element_type::MPA);

// *****************************************************************************
element_type::element_type()
{
	set(local, 0, MPA);

	return;
}

// *****************************************************************************
element_type::element_type(tower_type_t tower_type,
		tower_ID_t tower_ID, chip_type_t chip_type)
{
	set(tower_type, tower_ID, chip_type);

	return;
}

// *****************************************************************************
void element_type::set(tower_type_t tower_type, tower_ID_t tower_ID,
        chip_type_t chip_type)
{
	set_tower_type(tower_type);
	set_tower_ID(tower_ID);
	set_chip_type(chip_type);

	return;
}

// *****************************************************************************
void element_type::set_tower_type(tower_type_t tower_type)
{
	this->tower_type = tower_type;

	return;
}

// *****************************************************************************
element_type::tower_type_t element_type::get_tower_type() const
{
	return (tower_type);
}

// *****************************************************************************
void element_type::set_tower_ID(tower_ID_t tower_ID)
{
	this->tower_ID = tower_ID;

	return;
}

// *****************************************************************************
element_type::tower_ID_t element_type::get_tower_ID() const
{
	return (tower_ID);
}

// *****************************************************************************
void element_type::set_chip_type(chip_type_t chip_type)
{
	this->chip_type = chip_type;

	return;
}

// *****************************************************************************
element_type::chip_type_t element_type::get_chip_type() const
{
    return (chip_type);
}

// *****************************************************************************
bool element_type::operator== (const element_type& rhs) const
{
    bool equal = true;

    equal &= (tower_type == rhs.tower_type);
    equal &= (tower_ID == rhs.tower_ID);
    equal &= (chip_type == rhs.chip_type);

    return (equal);
}

// *****************************************************************************
std::string element_type::get_string() const
{
    std::stringstream out_string;

    out_string << "[";

    if (*this == element_type::sof)
    {
        out_string << std::setw(17) << std::left << "SOF";
    }
    else if (*this == element_type::eof)
    {
        out_string << std::setw(17) << std::left << "EOF";
    }
    else
    {
        if (tower_type == local)
        {
            out_string << "tt=L,";
        }
        else
        {
            out_string << "tt=A,";
        }

        out_string << "id=0x" << std::hex << tower_ID << ",";

        if (chip_type == MPA)
        {
            out_string << "c=MPA";
        }
        else
        {
            out_string << "c=CBC";
        }
    }

    out_string << "]";

    return (out_string.str());
}

// *****************************************************************************
std::ostream& operator<< (std::ostream& stream, const element_type& type_field)
{
    stream << type_field.get_string();

    return (stream);
}

// *****************************************************************************
} // namespace PRBF
