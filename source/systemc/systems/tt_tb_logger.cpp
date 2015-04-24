/*!
 * @file tt_tb_logger.cpp
 * @author Christian Amstutz
 * @date April 24, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "tt_tb_logger.hpp"

// *****************************************************************************
BOOST_LOG_GLOBAL_LOGGER_INIT(sysC_logger, boost::log::sources::logger)
{
    boost::log::sources::logger lg;
    boost::log::add_file_log
    (
        boost::log::keywords::file_name = "TT_TB.log"
    );

    return lg;
}

// *****************************************************************************
unsigned int sim_time_nano_seconds()
{
    double factor_s_to_ns = 1.0e9;
    double sim_time_seconds = sc_time_stamp().to_seconds();
    unsigned int sim_time_nano_seconds = sim_time_seconds * factor_s_to_ns;

    return sim_time_nano_seconds;

}
