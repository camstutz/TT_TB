/*!
 * @file stub.hpp
 * @author Christian Amstutz
 * @date Jan 10, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "stub.hpp"

// *****************************************************************************
stub::stub(const int address, const int bend) : address(address), bend(bend) {

  return;
}

// *****************************************************************************
void stub::setAddress(const int address) {

  this->address = address;
  return;
}

// *****************************************************************************
int stub::getAddress() const {

  return address;
}

// *****************************************************************************
void stub::setBend(const int bend) {

  this->bend = bend;
  return;
}

// *****************************************************************************
int stub::getBend() const {

  return bend;
}

// *****************************************************************************
bool stub::operator == (const stub &rhs) const {

  return (rhs.address == address && rhs.bend == bend );
}

// *****************************************************************************
stub& stub::operator = (const stub & rhs) {

  address = rhs.address;
  bend = rhs.bend;

  return *this;
}

// *****************************************************************************
ostream& operator << (ostream &os, stub const &v) {

  os << "[" << v.address << "," << v.bend << "]";

  return os;
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const stub &v, const std::string &name) {

  sc_trace(tf, v.address, name + ".address");
  sc_trace(tf, v.bend, name + ".bend");

  return;
}
