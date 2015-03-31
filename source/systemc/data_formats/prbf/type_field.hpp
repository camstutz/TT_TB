/*!
 * @file type_field.hpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

// *****************************************************************************
class type_field
{
public:
    typedef enum
	{
    	local    = 0x0,
		adjacent = 0x1
    } tower_type_t;
    typedef unsigned int tower_ID_t;
    typedef enum
    {
		MPA = 0x0,
        CBC = 0x1,
    } chip_type_t;

    static const type_field sof;
    static const type_field eof;

    type_field();
    type_field(tower_type_t tower_type, tower_ID_t tower_ID, chip_type_t chip_type);
private:
    void init(tower_type_t tower_type, tower_ID_t tower_ID, chip_type_t chip_type);

public:
    void set_tower_type(tower_type_t tower_type);
    tower_type_t get_tower_type() const;
    void set_tower_ID(tower_ID_t tower_ID);
    tower_ID_t get_tower_ID() const;
    void set_chip_type(chip_type_t chip_type);
    chip_type_t get_chip_type() const;

    bool operator== (const type_field& rhs) const;

private:
    tower_type_t tower_type;
    tower_ID_t tower_ID;
    chip_type_t chip_type;
};
