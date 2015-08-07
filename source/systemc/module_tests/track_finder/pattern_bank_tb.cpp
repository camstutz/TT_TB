/*!
 * @file pattern_bank_tb.cpp
 * @author Christian Amstutz
 * @date August 5, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "pattern_bank_tb.hpp"

// *****************************************************************************

// *****************************************************************************
pattern_bank_tb::pattern_bank_tb() :
        patterns(6)
{
    log_buffer << std::endl
            << "Simulation Output of Pattern Bank TB:" << std::endl
            << "*************************************" << std::endl;

    patterns.generate_patterns_straight(20);
    log_buffer << patterns.print_pattern_bank() << std::endl;
    log_buffer << patterns.print_reverse_tables() << std::endl;
    patterns.store_text_binary_file("text_binary_straight_test.dat");
    patterns.store_text_file("text_straight_test.dat");

    patterns.clear();
    patterns.load_text_binary_file("text_binary_test_bank.dat");
    log_buffer << patterns.print_pattern_bank() << std::endl;

    //patterns.clear();
    //patterns.load_CMSSW_patterns("test_bank.pbk");

    return;
}

// *****************************************************************************
pattern_bank_tb::~pattern_bank_tb()
{
    std::cout << log_buffer.str();

    return;
}
