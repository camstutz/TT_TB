/*!
 * @file header.cpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "header.hpp"

using namespace PRBF;

// *****************************************************************************
header::header()
{
    type_field = element_type::sof;
    set_bunch_crossing_ID(0);

    return;
}

// *****************************************************************************
header::header(bunch_crossing_ID_t bunch_crossing)
{
    set_bunch_crossing_ID(bunch_crossing);

    return;
}

// *****************************************************************************
void header::set_type_field(element_type type_field)
{
    std::cerr << "Error: PRBF::header - Type field cannot be altered."
              << std::endl;

    return;
}

// *****************************************************************************
void header::set_bunch_crossing_ID(bunch_crossing_ID_t bunch_crossing)
{
    this->bunch_crossing_ID = bunch_crossing;

    return;
}

// *****************************************************************************
header::bunch_crossing_ID_t header::get_bunch_crossing_ID() const
{
    return (bunch_crossing_ID);
}
