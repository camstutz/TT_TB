/*!
 * @file TT_configuration.hpp
 * @author Christian Amstutz
 * @date Apr 2, 2014
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

//* Number of bits to represent the address of a stub at the front end chip output
#define FE_STUB_STRIP_BITS 8
//* Number of bits to represent the bend of a stub at the front end chip output
#define FE_STUB_BEND_BITS 5

#define DC_WORD_TIME_BITS 3
#define DC_WORD_FE_BITS 3

#define DO_STUB_PHI_BITS 4
#define DO_STUB_Z_BITS 4
#define DO_STUB_FECHIP_BITS 3
#define DO_STUB_STRIP_BITS 5
#define DO_STUB_BEND_BITS 0

// Number of hits that can be handled by a single front end chip
#define MAX_HITS_PER_FE_CHIP       3

// Bit width of the data concentrator output
#define DC_OUTPUT_WIDTH           32
// Duration in cycles of the window in the data concentrator
#define NR_DC_WINDOW_CYCLES        8
// Number of stubs transmitted by the data concentrator
#define NR_DC_OUT_STUBS           ((DC_OUTPUT_WIDTH-2)*NR_DC_WINDOW_CYCLES)/(1+DC_WORD_TIME_BITS+DC_WORD_FE_BITS+FE_STUB_STRIP_BITS+FE_STUB_BEND_BITS)
#define NR_DO_OUT_STUBS           12

#define NR_AM_BOARDS               4

#define NR_DETECTOR_LAYERS         6  // Number of detector sensor modules existing at the detector
#define NR_DETECTOR_PHI            1  // Number of sensors in the circumference of the detector
#define NR_DETECTOR_Z              1  // Number of sensors on length of the detector
#define NR_FE_CHIP_PER_MODULE      8  // Number of front-end chips per sensor module

#define NR_SENSOR_MODULES NR_DETECTOR_LAYERS*NR_DETECTOR_PHI*NR_DETECTOR_Z // Total number of sensor modules of a detector

#define STUB_FIFO_DEPTH            50

#define AM_BOARD_LATENCY           18
#define AM_BOARD_PATTERN_WIDTH     18
#define AM_BOARD_ROAD_WIDTH        21
#define AM_BOARD_PATTERN_NR        256
