/*!
 * @file PRBF.hpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "PRBF_frame.hpp"
#include "stub_PRBF0.hpp"
#include "stub_PRBF1.hpp"
#include "stub_PRBF2.hpp"

using namespace PRBF;

typedef PRBF_frame<stub_PRBF0> PRBF_0;
typedef PRBF_frame<stub_PRBF1> PRBF_1;
typedef PRBF_frame<stub_PRBF2> PRBF_2;
