/*!
 * @file data_organizer.hpp
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

#include <array>
#include <sstream>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "stub_ext.hpp"

/*!
 * @brief
 */

class data_organizer : public sc_module {

public:
  typedef struct {
    sc_out<bool> *dv;
    sc_out<stub_ext> *data;
  } stub_out_t;
  typedef std::array<stub_out_t, NR_DO_OUT_STUBS> stub_out_field_t;

  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<bool> rst;

  sc_in<sc_bv<DC_OUTPUT_WIDTH> > do_in;

  stub_out_field_t stub_out;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  data_organizer(sc_module_name _name);
  SC_HAS_PROCESS(data_organizer);

private:

};
