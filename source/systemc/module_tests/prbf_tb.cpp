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
    using namespace PRBF;

    element_type a(element_type::local, 0, element_type::MPA);
    element_type test_element_type;

	test_element_type = element_type::eof;
	a = element_type::sof;

	std::cout << "a is SOF: " << (a == element_type::sof) << std::endl;

	a.set_chip_type(element_type::CBC);
	a.set_tower_ID(2);
	a.set_tower_type(element_type::adjacent);

	std::cout << "a is EOF: " << (a == element_type::eof) << std::endl;

	header header1;
	trailer trailer1;
	stub_element stub_element;

	header1.set_type_field(element_type::sof);
	header1.set_bunch_crossing_ID(1);

	trailer1.set_type_field(element_type::eof);
	trailer1.set_stub_count(4);

	stub_element.get_type_field();

	stub_PRBF0 stub2;

	stub2.set_strip(2);
	stub2.set_bend(5);

	return;
}
