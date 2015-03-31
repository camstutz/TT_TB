/*!
 * @file type_field.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "type_field.hpp"

// *****************************************************************************

const type_field type_field::sof = type_field(type_field::local, 2, type_field::MPA);
const type_field type_field::eof = type_field(type_field::local, 1, type_field::MPA);

// *****************************************************************************
type_field::type_field()
{
	init(local, 0, MPA);

	return;
}

// *****************************************************************************
type_field::type_field(tower_type_t tower_type,
		tower_ID_t tower_ID, chip_type_t chip_type)
{
	init(tower_type, tower_ID, chip_type);

	return;
}

// *****************************************************************************
void type_field::init(tower_type_t tower_type, tower_ID_t tower_ID, chip_type_t
        chip_type)
{
	set_tower_type(tower_type);
	set_tower_ID(tower_ID);
	set_chip_type(chip_type);

	return;
}

// *****************************************************************************
void type_field::set_tower_type(tower_type_t tower_type)
{
	this->tower_type = tower_type;

	return;
}

// *****************************************************************************
type_field::tower_type_t type_field::get_tower_type() const
{
	return (tower_type);
}

// *****************************************************************************
void type_field::set_tower_ID(tower_ID_t tower_ID)
{
	this->tower_ID = tower_ID;

	return;
}

// *****************************************************************************
type_field::tower_ID_t type_field::get_tower_ID() const
{
	return (tower_ID);
}

// *****************************************************************************
void type_field::set_chip_type(chip_type_t chip_type)
{
	this->chip_type = chip_type;

	return;
}

// *****************************************************************************
type_field::chip_type_t type_field::get_chip_type() const
{
    return (chip_type);
}

// *****************************************************************************
bool type_field::operator== (const type_field& rhs) const
{
    bool equal = true;

    equal &= (tower_type == rhs.tower_type);
    equal &= (tower_ID == rhs.tower_ID);
    equal &= (chip_type == rhs.chip_type);

    return (equal);
}
