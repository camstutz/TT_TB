/*!
 * @file HitEvent.hpp
 * @author Christian Amstutz
 * @date Dec 10, 2013
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#pragma once


/*!
 * @brief
 */
struct HitEvent {
  int timeStamp;
  int layer;
  int phiCoordinate;
  int zCoordinate;
  int frontEndChipNr;
  int stubAddress;
  int stubBend;
};
