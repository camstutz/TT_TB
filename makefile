include_dirs := /usr/local/lib/systemc-2.3.1/include /usr/local/include/root
include_dirs += source/systemc/libraries/systemc_helpers/sc_map/include source/systemc/libraries/systemc_helpers/nbits/include source/systemc/libraries/systemc_helpers/sc_analyzer/include source/systemc/libraries/systemc_helpers/sc_delay/include

librarypaths := /usr/local/lib/systemc-2.3.1/lib-linux64 /usr/local/lib/root source/systemc/libraries/systemc_helpers
libraries := systemc_helpers
libraries += systemc
libraries += boost_system boost_serialization boost_iostreams boost_thread boost_log
libraries += Hist Gpad Thread Physics Graf Graf3d Matrix RIO Net Core Tree

modules   := source/systemc/systems

DFDIR     := source/systemc/data_formats
modules   += $(DFDIR)/CIC_frame $(DFDIR)/gbt_link_format $(DFDIR)/hit_file $(DFDIR)/HitSF $(DFDIR)/prbf $(DFDIR)/stub

MODULEDIR := source/systemc/modules
modules   += source/systemc/TT_configuration
modules   += $(MODULEDIR)/hit_generator
modules   += $(MODULEDIR)/frontend/sensor_module $(MODULEDIR)/frontend/frontend_chip $(MODULEDIR)/frontend/data_concentrator $(MODULEDIR)/frontend/gbt
modules   += $(MODULEDIR)/backend/dtc
modules   += $(MODULEDIR)/backend $(MODULEDIR)/backend/data_organizer $(MODULEDIR)/backend/processor_organizer
modules   += $(MODULEDIR)/backend/am_board $(MODULEDIR)/backend/am_board/am_input_module
modules   += $(MODULEDIR)/backend/am_board/track_finder $(MODULEDIR)/backend/am_board/track_finder/am_chip $(MODULEDIR)/backend/am_board/track_finder/hit_buffer
modules   += $(MODULEDIR)/backend/am_board/track_finder/hit_processor $(MODULEDIR)/backend/am_board/track_finder/pattern_bank
modules   += $(MODULEDIR)/backend/am_board/track_finder/pattern_memory $(MODULEDIR)/backend/am_board/track_finder/road_processor
modules   += $(MODULEDIR)/road_analyzer
modules   += source/systemc/libraries/CMSSW_extraction

sources     :=
sim_sources :=
tb_sources  :=

TBPATH     := source/systemc/module_tests
tb_sources += $(TBPATH)/TT_TB_testbench.cpp
#tb_sources += $(TBPATH)/hit_file_test.cpp
#tb_sources += $(TBPATH)/prbf_tb.cpp
tb_sources += $(TBPATH)/hit_generator_tb.cpp
tb_sources += $(TBPATH)/frontend_chip_cbc_tb.cpp $(TBPATH)/frontend_chip_mpa_tb.cpp
tb_sources += $(TBPATH)/data_concentrator_cbc_tb.cpp $(TBPATH)/data_concentrator_mpa_tb.cpp
tb_sources += $(TBPATH)/gbt_tb.cpp 
tb_sources += $(TBPATH)/dtc_tb.cpp $(TBPATH)/dtc_input_unit_tb.cpp $(TBPATH)/dtc_output_unit_tb.cpp
tb_sources += $(TBPATH)/backend_common/bx_stub_buffer_tb.cpp $(TBPATH)/backend_common/input_collector_tb.cpp $(TBPATH)/backend_common/time_demux_tb.cpp
tb_sources += $(TBPATH)/data_organizer/data_organizer_tb.cpp
tb_sources += $(TBPATH)/processor_organizer/po_layer_splitter_tb.cpp $(TBPATH)/processor_organizer/processor_organizer_tb.cpp
tb_sources += $(TBPATH)/am_board/am_input_module_one_layer_tb.cpp $(TBPATH)/am_board/am_input_module_tb.cpp
tb_sources += $(TBPATH)/track_finder/pattern_bank_tb.cpp
#tb_sources += $(TBPATH)/track_finder/am_chip_tb.cpp
tb_sources += $(TBPATH)/trigger_tower_tb.cpp
 
#################################################################################################

source-to-object = $(subst .cpp,.o,$(filter %.cpp,$1)) \
                   $(subst .cc,.o,$(filter %.cc,$1))   \
                   $(subst .c,.o,$(filter %.c,$1))
                   
subdirectory = $(patsubst %/module.mk,%,                            \
                   $(word                                           \
                       $(words &(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

include $(addsuffix /module.mk,$(modules))

objects          := $(call source-to-object,$(sources))
dependencies     := $(subst .o,.d,$(objects))
execs            := $(addsuffix _exec, $(programs))
sim_objects      := $(call source-to-object,$(sim_sources))
sim_dependencies := $(subst .o,.d,$(sim_objects))
tb_objects       := $(call source-to-object,$(tb_sources))
tb_dependencies  := $(subst .o,.d,$(tb_objects))

LINK_LIBS       = $(addprefix -l,$(libraries))
LINK_LIBPATHS   = $(addprefix -L,$(librarypaths))

CC       := g++
CPPFLAGS := -Wall -g3 -O0 -std=c++11 $(addprefix -I,$(include_dirs)) $(LINK_LIBPATHS) $(LINK_LIBS)

MV  := mv -f
RM  := rm -f
SED := sed

.PHONY: all
all: TT_TB_sim libraries

TT_TB_sim: $(dependencies) $(objects) $(sim_dependencies) $(sim_objects)
	$(CC) source/systemc/systems/TT_TB_sim.cpp -o $@ $(sim_objects) $(objects) $(CPPFLAGS) $(LINK_LIBS) $(TARGET_ARCH) -pthread

.PHONY: test
test: TT_TB_test libraries

TT_TB_test: $(dependencies) $(objects) $(tb_dependencies) $(tb_objects)
	$(CC) -o $@ $(tb_objects) $(objects) $(CPPFLAGS) $(LINK_LIBS) $(TARGET_ARCH) -pthread

.PHONY: clean
clean:
	$(RM) $(objects) $(execs) $(dependencies) $(sim_dependencies) $(sim_objects) $(tb_dependencies) $(tb_objects)
	$(RM) TT_TB_sim TT_TB_test source/systemc/module_tests/TT_TB_testbench.o
	+make clean -C source/systemc/libraries/systemc_helpers

.PHONY: libraries
libraries:
	+make -C source/systemc/libraries/systemc_helpers
	
%.d: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cpp,.d,$<)

%.d: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cc,.d,$<)

#%.o: %.cpp %.cc
#	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@

-include $(dependencies)
-include $(tb_dependencies)
