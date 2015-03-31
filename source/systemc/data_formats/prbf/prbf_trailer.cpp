/*!
 * @file prbf_trailer.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "prbf_trailer.hpp"

// *****************************************************************************
prbf_trailer::prbf_trailer()
{
    type_field = prbf_element_type::eof;
    stub_count = 0;

    return;
}
// *****************************************************************************
void prbf_trailer::set_stub_count(stub_count_t stub_count)
{
    this->stub_count = stub_count;

    return;
}

// *****************************************************************************
prbf_trailer::stub_count_t prbf_trailer::get_stub_count() const
{
    return (stub_count);
}
