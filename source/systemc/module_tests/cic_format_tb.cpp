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
    std::cout << my_header << std::endl;
    std::cout << my_trailer << std::endl << std::endl;

    header my_header2(header::MPA, header::fe_0_ERROR, 4);
    std::cout << my_header2 << std::endl << std::endl;

    stub_CBC stub1(1,1,1,1);
    stub_MPA stub2(2,2,2,2,2);

    std::cout << stub1 << std::endl;
    std::cout << stub2 << std::endl << std::endl;

    CIC_frame_CBC my_frame1;
    std::cout << my_frame1.get_string() << std::endl;

    my_frame1.add_stub(stub_CBC(1,2,3,4));
    std::cout << my_frame1.get_string() << std::endl << std::endl;

    CIC_frame_MPA my_frame2;
    my_frame2.add_stub(stub_MPA(2,3,4,5,3));
    my_frame2.add_stub(stub_MPA(5,6,7,8,9));
    my_frame2.add_stub(stub_MPA(8,7,6,5,4));
    std::cout << my_frame2.get_string();

	return;
}
