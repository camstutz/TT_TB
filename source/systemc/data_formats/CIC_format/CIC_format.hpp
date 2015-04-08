/*!
 * @file CIC_format.hpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "CIC_frame.hpp"
#include "stub_CBC.hpp"
#include "stub_MPA.hpp"

using namespace CIC;

typedef CIC_frame<stub_CBC> CIC_frame_CBC;
typedef CIC_frame<stub_MPA> CIC_frame_MPA;
