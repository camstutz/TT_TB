/*!
 * @file HitSF.h
 * @author Christian Amstutz
 * @date August 3, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#ifndef _HITSF_H_
#define _HITSF_H_

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

/**
  \brief A hit in the detector for the Track Trigger Simulation Framework
**/
class HitSF
{
public :
    typedef int event_t;
    typedef bool flag_t;
    typedef int layer_t;
    typedef int ladder_t;
    typedef int module_t;
    typedef int segment_t;
    typedef int chip_t;
    typedef int strip_t;
    typedef int pixel_t;
    typedef int bend_t;
    typedef unsigned int stubId_t;
    typedef float coord_t;

    /**
      \brief Constructor
      \param misPS Indicates if the sensor module is a PS module
      \param misB Indicates if the sensor module is a module in the barrel
             section
      \param misE Indicates if the sensor module is a module of the endcaps
      \param l The layer of the hit
      \param lad The ladder of the hit
      \param zp The Z position of the module
      \param seg The segment of the hit in the module
      \param chip The front end chip id within a module segment
      \param strip The strip touched
      \param pixel The pixel touched
      \param bend The bend of the stub
      \param idx The index of the stub creating this hit
      \param p_x The X coordinate of the hit in the tracker
      \param p_y The Y coordinate of the hit in the tracker
      \param p_z The Z coordinate of the hit in the tracker
    **/
    HitSF(event_t event, flag_t misPS, flag_t misB, flag_t misE, layer_t l,
        ladder_t lad, module_t zp, segment_t seg, chip_t chip, strip_t strip,
        pixel_t pixel, bend_t bend, stubId_t idx, coord_t p_x, coord_t p_y,
        coord_t p_z);

    HitSF(bool *valid, std::string fileLine);

    /**
      \brief The copy Constructor
    **/
    HitSF(const HitSF& h);

    /**
      \brief Get the LHC event id to which the hit belongs.
      \return Id of the LHC event
    **/
    event_t getEvent() const;

    /**
      \brief Get if module is PS module
      \return True if the according sensor module is a PS modules, otherwise
              false
    **/
    flag_t getModuleIsPS() const;

    /**
      \brief Get if module is in the barrel region
      \return True if the according sensor module is in the barrel region
              otherwise false
    **/
    flag_t getModuleIsBarrel() const;

    /**
      \brief Get if module is part of the endcaps
      \return True if the according sensor module belongs to the endcaps
              otherwise false
    **/
    flag_t getModuleIsEndcap() const;

    /**
      \brief Get the layer of the hit
      \return The layer of the Hit
    **/
    layer_t getLayer() const;

    /**
      \brief Get the ladder of the hit
      \return The ladder of the Hit
    **/
    ladder_t getLadder() const;

    /**
      \brief Get the Z position of the module of the hit
      \return The position of the module
    **/
    module_t getModule() const;

    /**
      \brief Get the segment of the hit
      \return The segment of the Hit
    **/
    segment_t getSegment() const;

    /**
      \brief Get chip within the segment of the hit
      \return The chip id of the Hit
    **/
    chip_t getChip() const;

    /**
      \brief Get the strip position of the hit
      \return The strip of the Hit
    **/
    strip_t getStrip() const;

    /**
      \brief Get the pixel position of the hit
      \return The pixel of the Hit
    **/
    pixel_t getPixel() const;

    /**
      \brief Get the bend of the hit
      \return The bend of the Hit
    **/
    bend_t getBend() const;

    /**
      \brief Get the ID of the hit in the event
      \return The ID of the Hit
    **/
    stubId_t getID() const;

    /**
      \brief Get the X coordinate of the hit
      \return The distance in cm
    **/
    coord_t getX() const;

  /**
    \brief Get the Y coordinate of the hit
    \return The distance in cm
  **/
    coord_t getY() const;

    /**
      \brief Get the Z coordinate of the hit
      \return The distance in cm
    **/
    coord_t getZ() const;

    /**
      \brief Get one line for the hit file, used by the Simulation Framework
      \return One line for the hit file of the Simulation Framework
    **/
    std::string getFileLine();

private :
    event_t event;
    flag_t moduleIsPS;
    flag_t moduleIsBarrel;
    flag_t moduleIsEndcap;
    int layer;
    int ladder;
    int module;
    int segment;
    int chip;
    int strip;
    int pixel;
    int bend;
    int stub_idx;
    float x;
    float y;
    float z;

    static const unsigned int event_w = 6;
    static const unsigned int layer_w = 2;
    static const unsigned int ladder_w = 2;
    static const unsigned int module_w = 2;
    static const unsigned int segment_w = 1;
    static const unsigned int chip_w = 1;
    static const unsigned int strip_w = 3;
    static const unsigned int pixel_w = 2;
    static const unsigned int bend_w = 2;
    static const unsigned int stubId_w = 5;

    /**
      \brief Allows to display a Hit on the console
    **/
    friend ostream& operator<<(ostream& out, const HitSF& h);
};

#endif // _HITSF_H_
