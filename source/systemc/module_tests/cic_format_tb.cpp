/*!
 * @file cic_format_tb.cpp
 * @author Christian Amstutz
 * @date April 7, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "cic_format_tb.hpp"

void cic_format_tb()
{
    using namespace CIC;

    header my_header;
    trailer my_trailer;

    std::cout << "CIC format test bench" << std::endl;
    std::cout << my_header.get_string() << std::endl;
    std::cout << my_trailer.get_string() << std::endl << std::endl;

    header my_header2(header::MPA, header::fe_0_ERROR, 4);
    std::cout << my_header2.get_string() << std::endl;

	return;
}
