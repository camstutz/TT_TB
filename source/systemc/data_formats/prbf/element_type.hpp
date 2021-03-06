/*!
 * @file element_type.hpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <iomanip>

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************
class element_type
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
	    CBC = 0x0,
        MPA = 0x1,
    } chip_type_t;

    static const element_type sof;
    static const element_type eof;
    static const element_type local_CBC;
    static const element_type local_MPA;

    element_type();
    element_type(tower_type_t tower_type, tower_ID_t tower_ID, chip_type_t chip_type);

    void set(tower_type_t tower_type, tower_ID_t tower_ID, chip_type_t chip_type);

    void set_tower_type(tower_type_t tower_type);
    tower_type_t get_tower_type() const;
    void set_tower_ID(tower_ID_t tower_ID);
    tower_ID_t get_tower_ID() const;
    void set_chip_type(chip_type_t chip_type);
    chip_type_t get_chip_type() const;

    bool operator== (const element_type& rhs) const;

    std::string get_string() const;

private:
    tower_type_t tower_type;
    tower_ID_t tower_ID;
    chip_type_t chip_type;
};

std::ostream& operator<< (std::ostream& stream, const element_type& type_field);

// *****************************************************************************
} // namespace PRBF
