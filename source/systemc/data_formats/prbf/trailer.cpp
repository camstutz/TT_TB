/*!
 * @file trailer.cpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trailer.hpp"

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************
trailer::trailer()
{
    type_field = element_type::eof;
    payload = 0;

    return;
}

// *****************************************************************************
void trailer::set_type_field(element_type type_field)
{
    std::cerr << "Error: PRBF::trailer - Type field cannot be altered."
              << std::endl;

    return;
}

// *****************************************************************************
void trailer::set_stub_count(stub_count_t stub_count)
{
    payload = stub_count;

    return;
}

// *****************************************************************************
trailer::stub_count_t trailer::get_stub_count() const
{
    return (payload);
}

// *****************************************************************************
} // namespace PRBF
