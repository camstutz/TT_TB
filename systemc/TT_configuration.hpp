/*!
 * @file TT_configuration.hpp
 * @author Christian Amstutz
 * @date Feb 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */


// Define the clock frequency and the period in nanoseconds of the LHC clock
#define LHC_CLOCK_FREQ 40000000
#define LHC_CLOCK_PERIOD_NS 25

// Number of bits to represent the address of a stub
#define NR_STUB_ADDRESS_BITS 8
// Number of bits to represent the bend of a stub
#define NR_STUB_BEND_BITS 5

// Number of hits that can be handled by a single front end chip
#define MAX_HITS_PER_FE_CHIP       3

// Bit width of the data concentrator output
#define DC_OUTPUT_WIDTH           32
// Duration in cycles of the window in the data concentrator
#define NR_DC_WINDOW_CYCLES        8
// Number of stubs transmitted by the data concentrator
//! todo: calculate this value
#define NR_DC_OUT_STUBS           12

#define NR_DETECTOR_LAYERS         6  // Number of detector sensor modules existing at the detector
#define NR_DETECTOR_PHI            1  // Number of sensors in the circumference of the detector
#define NR_DETECTOR_Z              1  // Number of sensors on length of the detector
#define NR_FE_CHIP_PER_MODULE      8  // Number of front-end chips per sensor module

#define NR_SENSOR_MODULES NR_DETECTOR_LAYERS*NR_DETECTOR_PHI*NR_DETECTOR_Z // Total number of sensor modules of a detector
