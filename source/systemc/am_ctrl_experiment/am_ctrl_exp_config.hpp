/*!
 * @file am_ctrl_experiment.hpp
 * @author Christian Amstutz
 * @date November 17, 2014
 *
 * @brief
 */

#pragma once

#define AMEXP_CLOCK_PERIOD_NS 10

#define LAYER_NUMBER 2
#define SS_BIT_WIDTH 2
#define AM_CHIP_PATTERN_NR 5000
#define AM_HITS_PER_ROAD_THRESHOLD 2

#define IDLE_EVENT  0xFFFF
#define START_EVENT 0xFFFE

typedef unsigned int hit_t;
typedef unsigned int superstrip_t;
typedef unsigned int substrip_t;
typedef unsigned int road_t;
