/*!
 * @file tt_tb_logger.hpp
 * @author Christian Amstutz
 * @date April 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#define BOOST_LOG_DYN_LINK 1
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

#include <string>
#include <iomanip>

// *****************************************************************************

BOOST_LOG_GLOBAL_LOGGER(sysC_logger, boost::log::sources::logger)

unsigned int sim_time_nano_seconds();

#define SYSTEMC_LOG                                                                  \
        BOOST_LOG(sysC_logger::get())                                                \
                << std::right << std::setw(6) << sim_time_nano_seconds() << " ns"    \
                << " @ " <<  std::left << std::setw(55) << this->name()              \
                << ": "
