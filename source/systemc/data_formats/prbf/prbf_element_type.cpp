/*!
 * @file prbf_element_type.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "prbf_element_type.hpp"

// *****************************************************************************

const prbf_element_type prbf_element_type::sof = prbf_element_type(prbf_element_type::local, 2, prbf_element_type::MPA);
const prbf_element_type prbf_element_type::eof = prbf_element_type(prbf_element_type::local, 1, prbf_element_type::MPA);

// *****************************************************************************
prbf_element_type::prbf_element_type()
{
	init(local, 0, MPA);

	return;
}

// *****************************************************************************
prbf_element_type::prbf_element_type(tower_type_t tower_type,
		tower_ID_t tower_ID, chip_type_t chip_type)
{
	init(tower_type, tower_ID, chip_type);

	return;
}

// *****************************************************************************
void prbf_element_type::init(tower_type_t tower_type, tower_ID_t tower_ID, chip_type_t
        chip_type)
{
	set_tower_type(tower_type);
	set_tower_ID(tower_ID);
	set_chip_type(chip_type);

	return;
}

// *****************************************************************************
void prbf_element_type::set_tower_type(tower_type_t tower_type)
{
	this->tower_type = tower_type;

	return;
}

// *****************************************************************************
prbf_element_type::tower_type_t prbf_element_type::get_tower_type() const
{
	return (tower_type);
}

// *****************************************************************************
void prbf_element_type::set_tower_ID(tower_ID_t tower_ID)
{
	this->tower_ID = tower_ID;

	return;
}

// *****************************************************************************
prbf_element_type::tower_ID_t prbf_element_type::get_tower_ID() const
{
	return (tower_ID);
}

// *****************************************************************************
void prbf_element_type::set_chip_type(chip_type_t chip_type)
{
	this->chip_type = chip_type;

	return;
}

// *****************************************************************************
prbf_element_type::chip_type_t prbf_element_type::get_chip_type() const
{
    return (chip_type);
}

// *****************************************************************************
bool prbf_element_type::operator== (const prbf_element_type& rhs) const
{
    bool equal = true;

    equal &= (tower_type == rhs.tower_type);
    equal &= (tower_ID == rhs.tower_ID);
    equal &= (chip_type == rhs.chip_type);

    return (equal);
}
