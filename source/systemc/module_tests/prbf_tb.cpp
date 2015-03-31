/*!
 * @file prbf_tb.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "prbf_tb.hpp"

void prbf_tb()
{
    type_field a(type_field::local, 0, type_field::MPA);
    type_field test_element_type;

	test_element_type = type_field::eof;
	a = type_field::sof;

	std::cout << "a is SOF: " << (a == type_field::sof) << std::endl;

	a.set_chip_type(type_field::CBC);
	a.set_tower_ID(2);
	a.set_tower_type(type_field::adjacent);

	std::cout << "a is EOF: " << (a == type_field::eof) << std::endl;

	return;
}
