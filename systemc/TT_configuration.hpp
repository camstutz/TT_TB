/*!
 * @file TT_configuration.hpp
 * @author Christian Amstutz
 * @date Dec 10, 2013
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#define NR_FRONTENDCHIP_PER_MODULE 8  // Number of front-end chips per sensor module
#define NR_DETECTOR_LAYERS         6  // Number of detector sensor modules existing at the detector
#define NR_DETECTOR_PHI            1  // Number of sensors in the circumference of the detector
#define NR_DETECTOR_Z              1  // Number of sensors on length of the detector

#define NR_SENSOR_MODULES NR_DETECTOR_LAYERS*NR_DETECTOR_PHI*NR_DETECTOR_Z // Total number of sensor modules of a detector
