/*!
 * @file stub_ext.hpp
 * @author Christian Amstutz
 * @date Feb 6, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <iostream>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "stub.hpp"

/*!
 * @brief
 */
class stub_ext {

public:
  static const unsigned int phi_width = 4;
  static const unsigned int z_width = 4;
  static const unsigned int fechip_width = 3;
  static const unsigned int strip_width = 5;
  static const unsigned int bend_width = 0;
  static const unsigned int stub_width = phi_width + z_width + fechip_width
      + strip_width + bend_width;

  typedef sc_bv<phi_width> phi_coord_t;
  typedef sc_bv<z_width> z_coord_t;
  typedef sc_bv<fechip_width> fechip_nr_t;
  typedef sc_bv<strip_width> strip_nr_t;

  /** Constructor: All member variables are set to 0. */
  stub_ext();

  /** Setter function for the phi coordinate */
  void set_phi_coord(const phi_coord_t phi_coord);

  /** Getter function for the phi coordinate */
  phi_coord_t  get_phi_coord() const;

  /** Setter function for the z coordinate */
  void set_z_coord(const z_coord_t z_coord);

  /** Getter function for the z coordinate */
  z_coord_t  get_z_coord() const;

  /** Setter function for the front end chip number */
  void set_fechip_nr(const fechip_nr_t address);

  /** Getter function for the front end chip number */
  fechip_nr_t  get_fechip_nr() const;

  /** Setter function for the strip number */
  void set_strip_nr(const strip_nr_t address);

  /** Getter function for the strip number */
  strip_nr_t  get_strip_nr() const;

  /** Getter function for the whole extended stub as a bit vector */
  sc_bv<stub_width> getBitVector() const;

  /** Comparison of two extended stub objects */
  bool operator == (const stub_ext &rhs) const;

  /** Assignment operator for extended stubs */
  stub_ext& operator = (const stub_ext & rhs);

  /** Output function to print the address and bend of the extended stub. The format is:
   * [phi,z,fechip,strip] */
  friend ostream& operator << (ostream &os, stub_ext const &v);

  /** Function for tracing support in SystemC */
  friend void sc_trace(sc_trace_file *tf, const stub_ext &v, const std::string &name);

private:

  /** Phi coordinate from which the extended stub originates */
  phi_coord_t phi_coord;

  /** Z coordinate from which the extended stub originates */
  z_coord_t z_coord;

  /** Front End Chip number from which the extended stub originates */
  fechip_nr_t fechip_nr;

  /** Strip number from which the extended stub originates */
  strip_nr_t strip_nr;

};
