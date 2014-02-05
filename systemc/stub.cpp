/*!
 * @file stub.cpp
 * @author Christian Amstutz
 * @date Feb 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "stub.hpp"

// *****************************************************************************
stub::stub(const stub::stub_address_t address, const stub::stub_bend_t bend) :
    address(address),
    bend(bend) {

  return;
}

// *****************************************************************************
void stub::setAddress(const stub::stub_address_t address) {

  this->address = address;
  return;
}

// *****************************************************************************
stub::stub_address_t stub::getAddress() const {

  return address;
}

// *****************************************************************************
void stub::setBend(const stub::stub_bend_t bend) {

  this->bend = bend;
  return;
}

// *****************************************************************************
stub::stub_bend_t stub::getBend() const {

  return bend;
}

// *****************************************************************************
sc_bv<NR_STUB_ADDRESS_BITS + NR_STUB_BEND_BITS> stub::getBitVector() const {

  return ( (sc_bv<NR_STUB_ADDRESS_BITS>(address),
            sc_bv<NR_STUB_BEND_BITS>(bend)) );
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

  os << "[" << std::hex << v.address.to_uint()
     << "," << v.bend.to_uint() << "]";

  return os;
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const stub &v, const std::string &name) {

  sc_trace(tf, v.address, name + ".address");
  sc_trace(tf, v.bend, name + ".bend");

  return;
}
