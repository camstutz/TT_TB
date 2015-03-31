/*!
 * @file prbf_header.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "prbf_header.hpp"

// *****************************************************************************
prbf_header::prbf_header()
{
    type_field = prbf_element_type::sof;
    bunch_crossing_ID = 0;

    return;
}

// *****************************************************************************
void prbf_header::set_bunch_crossing_ID(bunch_crossing_ID_t bunch_crossing)
{
    this->bunch_crossing_ID = bunch_crossing;

    return;
}

// *****************************************************************************
prbf_header::bunch_crossing_ID_t prbf_header::get_bunch_crossing_ID() const
{
    return (bunch_crossing_ID);
}
