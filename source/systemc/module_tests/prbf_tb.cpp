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
    prbf_element_type a(prbf_element_type::local, 0, prbf_element_type::MPA);
    prbf_element_type test_element_type;

	test_element_type = prbf_element_type::eof;
	a = prbf_element_type::sof;

	std::cout << "a is SOF: " << (a == prbf_element_type::sof) << std::endl;

	a.set_chip_type(prbf_element_type::CBC);
	a.set_tower_ID(2);
	a.set_tower_type(prbf_element_type::adjacent);

	std::cout << "a is EOF: " << (a == prbf_element_type::eof) << std::endl;

	prbf_header header1;
	prbf_trailer trailer1;
	prbf_stub_element stub_element;

	header1.set_type_field(prbf_element_type::sof);
	header1.set_bunch_crossing_ID(1);

	trailer1.set_type_field(prbf_element_type::eof);
	trailer1.set_stub_count(4);

	stub_element.get_type_field();

	stub_PRBF0 stub2;

	stub2.set_strip(2);
	stub2.set_bend(5);

	return;
}
