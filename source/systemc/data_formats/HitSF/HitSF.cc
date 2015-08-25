/*!
 * @file HitSF.cc
 * @author Christian Amstutz
 * @date August 3, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "HitSF.h"

// *****************************************************************************
HitSF::HitSF(event_t event, flag_t misPS, flag_t misB, flag_t misE, layer_t l,
    ladder_t lad, module_t zp, segment_t seg, chip_t chip, strip_t strip,
    pixel_t pixel, bend_t bend, stubId_t idx, coord_t p_x, coord_t p_y,
    coord_t p_z)
{
    this->event = event;
    this->moduleIsPS = misPS;
    this->moduleIsBarrel = misB;
    this->moduleIsEndcap = misE;
    this->layer = l;
    this->ladder = lad;
    this->module = zp;
    this->segment = seg;
    this->chip = chip;
    this->strip = strip;
    this->pixel = pixel;
    this->bend = bend;
    this->stub_idx = idx;
    this->x = p_x;
    this->y = p_y;
    this->z = p_z;
}

// *****************************************************************************
HitSF::HitSF(bool *valid, std::string fileLine)
{
    std::stringstream fileLineStream(fileLine);
    fileLineStream >> std::dec
                   >> event
                   >> stub_idx
                   >> moduleIsPS
                   >> moduleIsBarrel
                   >> moduleIsEndcap
                   >> layer
                   >> ladder
                   >> module
                   >> segment
                   >> chip
                   >> strip
                   >> pixel
                   >> bend;
    if ( !fileLineStream.fail() )
    {
        *valid = true;
    }
    else
    {
        *valid = false;
    }

    x = 0;
    y = 0;
    z = 0;

    return;
}

// *****************************************************************************
HitSF::HitSF(const HitSF& h)
{
    this->event = h.event;
    this->moduleIsPS = h.moduleIsPS;
    this->moduleIsBarrel = h.moduleIsBarrel;
    this->moduleIsEndcap = h.moduleIsEndcap;
    this->layer = h.layer;
    this->ladder = h.ladder;
    this->module = h.module;
    this->segment = h.segment;
    this->chip = h.chip;
    this->strip = h.strip;
    this->pixel = h.pixel;
    this->bend = h.bend;
    this->stub_idx = h.stub_idx;
    this->x = h.x;
    this->y = h.y;
    this->z = h.z;
}

// *****************************************************************************
HitSF::event_t HitSF::getEvent() const
{
    return event;
}

// *****************************************************************************
HitSF::flag_t HitSF::getModuleIsPS() const
{
    return moduleIsPS;
}

// *****************************************************************************
HitSF::flag_t HitSF::getModuleIsBarrel() const
{
    return moduleIsBarrel;
}

// *****************************************************************************
HitSF::flag_t HitSF::getModuleIsEndcap() const
{
    return moduleIsEndcap;
}

// *****************************************************************************
HitSF::layer_t HitSF::getLayer() const
{
    return layer;
}

// *****************************************************************************
HitSF::ladder_t HitSF::getLadder() const
{
    return ladder;
}

// *****************************************************************************
HitSF::module_t HitSF::getModule() const
{
    return module;
}

// *****************************************************************************
HitSF::segment_t HitSF::getSegment() const
{
    return segment;
}

// *****************************************************************************
HitSF::chip_t HitSF::getChip() const
{
    return chip;
}

// *****************************************************************************
HitSF::strip_t HitSF::getStrip() const
{
    return strip;
}

// *****************************************************************************
HitSF::pixel_t HitSF::getPixel() const
{
    return pixel;
}

// *****************************************************************************
HitSF::bend_t HitSF::getBend() const
{
    return bend;
}

// *****************************************************************************
HitSF::stubId_t HitSF::getID() const
{
    return stub_idx;
}

// *****************************************************************************
HitSF::coord_t HitSF::getX() const
{
    return x;
}

// *****************************************************************************
HitSF::coord_t HitSF::getY() const
{
    return y;
}

// *****************************************************************************
HitSF::coord_t HitSF::getZ() const
{
    return z;
}

// *****************************************************************************
std::string HitSF::getFileLine()
{
    std::stringstream fileLine;

    fileLine << std::dec;
    fileLine << setw(event_w) << event << " ";
    fileLine << setw(stubId_w) << stub_idx << " ";
    fileLine << moduleIsPS << " ";
    fileLine << moduleIsBarrel << " ";
    fileLine << moduleIsEndcap << " ";
    fileLine << setw(layer_w) << layer << " ";
    fileLine << setw(ladder_w) << ladder << " ";
    fileLine << setw(module_w) << module << " ";
    fileLine << setw(segment_w) << segment << " ";
    fileLine << setw(chip_w) << chip << " ";
    fileLine << setw(strip_w) << strip << " ";
    fileLine << setw(pixel_w) << pixel << " ";
    fileLine << setw(bend_w) << bend << " ";

    return fileLine.str();
}

// *****************************************************************************
ostream& operator<<(ostream& out, const HitSF& h) {

      // Output calculated stub data
  out << "Stub (" << std::dec << std::setw(HitSF::stubId_w) << h.stub_idx << "): ";
  
  if (h.moduleIsPS) {
    out << "PS in ";
  }
  else {
    out << "2S in ";
  }
  
  if (h.moduleIsBarrel) {
    out << "Barrel: ";
  }
  else if (h.moduleIsEndcap) {
    out << "Endcap: ";
  }
  else {
    out << "?     : ";
  }
   
  out << std::dec;
  out << "layer=" << std::setw(HitSF::layer_w) << h.layer;
  out << ", ladder=" << std::setw(HitSF::ladder_w) << h.ladder;
  out << ", module=" << std::setw(HitSF::module_w) << h.module;
  out << std::endl;

  out << "   segment=" << h.segment;
  out << ", chip=" << h.chip;
  out << ", strip=" << std::setw(HitSF::strip_w) << h.strip;
  if (h.moduleIsPS) {
    out << ", pixel=" << std::setw(HitSF::pixel_w) << h.pixel;
  }
  out << " - bend=" << std::setw(HitSF::bend_w) << h.bend;
  out << std::endl;
      
  out << "   x:" << h.x;
  out << ", y:" << h.y;
  out << ", z: " << h.z;
  out << std::endl;

  return out;
}
