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
	stub_element<stub_PRBF0> stub_element;

	header1.set_bunch_crossing_ID(1);

	trailer1.set_type_field(element_type::eof);
	trailer1.set_stub_count(4);

	stub_element.get_type_field();

	stub_PRBF0 stub2;

	stub2.set_strip(2);
	stub2.set_bend(5);

	PRBF_0 frame0(0x12);
	PRBF_0::stub_t stub;
	stub.set(0x1,0x0,0x3,0x4,0x2,0x3);
    PRBF_0::stub_element_t stub_cont(element_type::local_CBC, stub);
	frame0.add_stub(stub_cont);
	stub.set(0x2,0x0,0x3,0x23,0x6);
	stub_cont.set_stub(stub);
	frame0.add_stub(stub_cont);

	std::cout << frame0.get_trailer().get_stub_count() << std::endl;

	std::cout << frame0.get_header().get_type_field() << std::endl;
	std::cout << "Header: " << frame0.get_header() << std::endl;
	std::cout << "Trailer: " << frame0.get_trailer() << std::endl;

    std::cout << std::endl;
	std::cout << frame0 << std::endl;
    std::cout << "Size: " << sizeof(frame0) << std::endl;
    std::cout << std::endl;

    PRBF_1 frame1(0x14);
    PRBF_1::stub_t stub_1;
    stub_1.set(0x5, 0x1, 0x0, 0x3, 0x4, 0x2, 0x3);
    std::cout << "STUB: " << stub_1 << std::endl;
    PRBF_1::stub_element_t stub_cont_1(element_type::local_MPA, stub_1);
    frame1.add_stub(stub_cont_1);
    stub_1.set(0x6, 0x1, 0x0, 0x3, 0x4, 0x2, 0x3);
    stub_cont_1.set_stub(stub_1);
    frame1.add_stub(stub_cont_1);

    std::cout << frame1 << std::endl;
    std::cout << "Size: " << sizeof(frame1);
    std::cout << std::endl << std::endl;

    PRBF_2 frame2(0xA);
    PRBF_2::stub_t stub_2;
    stub_2.set(0x1, 0x5, 0x1, 0x0, 0x3, 0x4, 0x2, 0x3);
    PRBF_2::stub_element_t stub_cont_2(element_type::local_MPA, stub_2);
    frame2.add_stub(stub_cont_2);
    stub_2.set(0x3, 0x6, 0x1, 0x0, 0x3, 0x4, 0x2, 0x3);
    stub_cont_2.set_stub(stub_2);
    frame2.add_stub(stub_cont_2);

    std::cout << frame2 << std::endl;
    std::cout << "Size: " << sizeof(frame2);
    std::cout << std::endl << std::endl;


	return;
}
