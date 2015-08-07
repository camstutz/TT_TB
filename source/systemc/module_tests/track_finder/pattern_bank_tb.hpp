/*!
 * @file pattern_bank_tb.hpp
 * @author Christian Amstutz
 * @date August 5, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/am_board/track_finder/pattern_bank/pattern_bank.hpp"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class pattern_bank_tb
{
public:
    pattern_bank patterns;

    pattern_bank_tb();
    ~pattern_bank_tb();

private:
    std::ostringstream log_buffer;
};
