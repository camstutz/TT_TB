/*!
 * @file hit_file_test.cpp
 * @author Christian Amstutz
 * @date June 25, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_file_test.hpp"

void hit_file_test()
{
    hit_file test_file;
    if (test_file.open("hit_file_test_hits.txt"))
    {
        std::cout << "hit_file opened" << std::endl;
    }
    else
    {
        std::cout << "error: opening hit_file" << std::endl;
    }

    hit* new_hit;
    while(test_file.data_ready())
    {
        test_file.get_next_hit(new_hit);
        std::cout <<  "hit:" << new_hit->get_value()->get_string() << std::endl;
        delete new_hit;
    }

    test_file.open("hit_file_test_hits.txt");
    test_file.write_old_format("hit_file_test_old_format.txt");
    test_file.close();

    return;
}
