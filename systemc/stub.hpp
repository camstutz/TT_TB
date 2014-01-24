/*!
 * @file stub.hpp
 * @author Christian Amstutz
 * @date Jan 24, 2014
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

/*!
 * @brief
 */
class stub {

private:
  /** Address of the strip on the silicon detector */
  unsigned int address;

  /** represents the difference of the hits between the two silicon detectors */
  unsigned int bend;

public:
  /** Constructor. The default values are 0 for the address and 0 for the bend.
   *  */
  stub(const int address=0, const int bend=0);

  /** Setter function for the address of the stub */
  void setAddress(const int address);

  /** Getter function for the address of the stub */
  int  getAddress() const;

  /** Setter function for the bend of the stub */
  void setBend(const int bend);

  /** Getter function for the address of the stub */
  int  getBend() const;

  /** Comparison of two stub objects */
  bool operator == (const stub &rhs) const;

  /** Assignment operator for stubs */
  stub& operator = (const stub & rhs);

  /** Output function to print the address and bend of the stub. The foramt is
   * [address,bend] */
  friend ostream& operator << (ostream &os, stub const &v);

  /** Function for tracing support in SystemC */
  friend void sc_trace(sc_trace_file *tf, const stub &v, const std::string &name);
};
