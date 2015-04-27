/*!
 * @file TT_configuration.hpp
 * @author Christian Amstutz
 * @date April 15, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

// Define the clock frequency and the period in nanoseconds of the LHC clock
#define LHC_CLOCK_FREQ 40000000
#define LHC_CLOCK_PERIOD_NS 25

#define FE_CBC_STUB_BX_BITS 0
#define FE_CBC_STUB_STRIP_BITS 8
#define FE_CBC_STUB_BEND_BITS 5

#define FE_MPA_STUB_BX_BITS 1
#define FE_MPA_STUB_STRIP_BITS 8
#define FE_MPA_STUB_BEND_BITS 5
#define FE_MPA_STUB_PIXEL_BITS 4

#define DC_STUB_BX_BITS 3
#define DC_STUB_FE_BITS 3
#define DC_OUT_HEADER_BITS 2

#define DO_STUB_PHI_BITS 4
#define DO_STUB_Z_BITS 4
#define DO_STUB_FECHIP_BITS 3
#define DO_STUB_STRIP_BITS 8
#define DO_STUB_BEND_BITS 0

// Number of hits that can be handled by a single front end chip
#define MAX_HITS_PER_CBC_FE_CHIP       3
#define COLLECTION_CYCLES_CBC_FE_CHIP  1
#define MAX_HITS_PER_MPA_FE_CHIP       2
#define COLLECTION_CYCLES_MPA_FE_CHIP  2

// Bit width of the data concentrator output
#define DC_OUTPUT_WIDTH           32
// Duration in cycles of the window in the data concentrator
#define NR_DC_WINDOW_CYCLES        8
// Number of stubs transmitted by the data concentrator
#define NR_DC_CBC_OUT_STUBS       12
#define NR_DC_MPA_OUT_STUBS       10
#define NR_DO_OUT_STUBS           12

#define DO_COUNTER_CORRECTION    -25
#define PO_COUNTER_CORRECTION    -27

#define NR_DTC_PER_PRB             1
#define NR_PRB_PER_TRIGGER_TOWER   2
#define NR_AM_BOARDS               2

#define NR_DETECTOR_MPA_LAYERS     3  // Number of layers with PS modules existing in the detector
#define NR_DETECTOR_CBC_LAYERS     3  // Number of layers with 2S modules existing in the detector
#define NR_DETECTOR_LAYERS         NR_DETECTOR_CBC_LAYERS + NR_DETECTOR_MPA_LAYERS
#define NR_DETECTOR_PHI            1  // Number of sensors in the circumference of the detector
#define NR_DETECTOR_Z              1  // Number of sensors on length of the detector
#define NR_FE_CHIP_SIDES           2
#define NR_FE_CHIP_PER_SIDE        8
#define NR_FE_CHIP_PER_MODULE      NR_FE_CHIP_SIDES * NR_FE_CHIP_PER_SIDE  // Number of front-end chips per sensor module

#define NR_TRIGGER_TOWERS NR_DETECTOR_PHI*NR_DETECTOR_Z
#define NR_TOWER_CONNECTIONS 4
#define NR_SENSOR_MODULES NR_DETECTOR_LAYERS*NR_DETECTOR_PHI*NR_DETECTOR_Z // Total number of sensor modules of a detector

#define STUB_FIFO_DEPTH            50

#define AM_HITS_PER_ROAD_THRESHOLD  6
#define AM_BOARD_LATENCY           18
#define AM_BOARD_PATTERN_WIDTH     16
#define AM_BOARD_ROAD_WIDTH        21
#define AM_BOARD_PATTERN_NR        1280

#define AMEXP_CLOCK_PERIOD_NS 10
#define SS_BIT_WIDTH 2

// Define delays
#define DC_output_delay 0
#define DTC_latency 0
#define DO_output_delay 0
#define AM_CHIP_LATENCY 0
#define PATTERN_MEMORY_LATENCY 0

// Signal types used between modules
#include "../data_formats/CIC_format/CIC_format.hpp"

#include "../data_formats/stub_sb.hpp"
#include "../data_formats/stub_vbxfsb.hpp"
#include "../data_formats/stub_bxpsb.hpp"
#include "../data_formats/stub_vbxpfsb.hpp"
#include "../data_formats/stub_pzfs.hpp"
#include "../data_formats/dc_out_word.hpp"

typedef stub_bxsb<FE_CBC_STUB_BX_BITS,
		          FE_CBC_STUB_STRIP_BITS,
                  FE_CBC_STUB_BEND_BITS,
                  FE_CBC_STUB_BX_BITS+FE_CBC_STUB_STRIP_BITS+FE_CBC_STUB_BEND_BITS> fe_cbc_stub_t;

typedef stub_bxpsb<FE_MPA_STUB_BX_BITS,
                   FE_MPA_STUB_PIXEL_BITS,
                   FE_MPA_STUB_STRIP_BITS,
                   FE_MPA_STUB_BEND_BITS,
                   FE_MPA_STUB_BX_BITS+FE_MPA_STUB_PIXEL_BITS+
                   FE_CBC_STUB_STRIP_BITS+FE_CBC_STUB_BEND_BITS> fe_mpa_stub_t;

typedef dc_out_word<DC_OUT_HEADER_BITS, DC_OUTPUT_WIDTH-DC_OUT_HEADER_BITS,
                    DC_OUTPUT_WIDTH> dc_out_t;

typedef stub_pzfs<DO_STUB_PHI_BITS, DO_STUB_Z_BITS, DO_STUB_FECHIP_BITS, DO_STUB_STRIP_BITS,
        DO_STUB_PHI_BITS+DO_STUB_Z_BITS+DO_STUB_FECHIP_BITS+DO_STUB_STRIP_BITS> do_stub_t;

typedef unsigned int hit_t;
typedef unsigned int superstrip_t;
typedef unsigned int substrip_t;
typedef unsigned int road_t;
