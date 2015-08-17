include_dirs := /usr/local/lib/systemc-2.3.1/include /usr/local/include/root
include_dirs += source/systemc/libraries/systemc_helpers/sc_map/include source/systemc/libraries/systemc_helpers/nbits/include source/systemc/libraries/systemc_helpers/sc_analyzer/include source/systemc/libraries/systemc_helpers/sc_delay/include

librarypaths := /usr/local/lib/systemc-2.3.1/lib-linux64 /usr/local/lib/root source/systemc/libraries/systemc_helpers
libraries := systemc_helpers
libraries += systemc
libraries += boost_system boost_serialization boost_iostreams boost_thread boost_log
libraries += Hist Gpad Thread Physics Graf Graf3d Matrix RIO Net Core Tree

modules   := source/systemc/systems

MODULEDIR := source/systemc/modules
modules   += $(MODULEDIR)/hit_generator
modules   += $(MODULEDIR)/frontend $(MODULEDIR)/frontend/frontend_chip $(MODULEDIR)/frontend/data_concentrator $(MODULEDIR)/frontend/gbt
modules   += $(MODULEDIR)/backend/dtc
modules   += $(MODULEDIR)/backend $(MODULEDIR)/backend/data_organizer $(MODULEDIR)/backend/processor_organizer
modules   += $(MODULEDIR)/backend/am_board $(MODULEDIR)/backend/am_board/am_input_module
modules   += $(MODULEDIR)/backend/am_board/track_finder $(MODULEDIR)/backend/am_board/track_finder/am_chip $(MODULEDIR)/backend/am_board/track_finder/hit_buffer
modules   += $(MODULEDIR)/backend/am_board/track_finder/hit_processor $(MODULEDIR)/backend/am_board/track_finder/pattern_bank
moduels   += $(MODULEDIR)/backend/am_board/track_finder/pattern_memory $(MODULEDIR)/backend/am_board/track_finder/road_processor
modules   += $(MODULEDIR)/road_analyzer

DFDIR := source/systemc/data_formats
modules   += $(DFDIR)/CIC_frame $(DFDIR)/gbt_link_format $(DFDIR)/hit_file $(DFDIR)/HitSF $(DFDIR)/prbf $(DFDIR)/stub

programs  := source/systemc/systems
sources   :=

#################################################################################################

#.SUFFIXES:

source-to-object = $(subst .cpp,.o,$(filter %.cpp,$1)) \
                   $(subst .cc,.o,$(filter %.cc,$1))   \
                   $(subst .c,.o,$(filter %.c,$1))
                   
subdirectory = $(patsubst %/module.mk,%,                            \
                   $(word                                           \
                       $(words &(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

objects       = $(call source-to-object,$(sources))
dependencies  = $(subst .o,.d,$(objects))
execs         = $(addsuffix _exec, $(programs))
LINK_LIBS     = $(addprefix -l,$(libraries))
LINK_LIBPATHS = $(addprefix -L,$(librarypaths))

CC       := g++
#CFLAGS   := -Wall -W -pedantic -ggdb3 -M
CPPFLAGS := -Wall -g3 -O0 -std=c++11 $(addprefix -I,$(include_dirs)) $(LINK_LIBPATHS) $(LINK_LIBS)

MV  := mv -f
RM  := rm -f
SED := sed

include $(addsuffix /module.mk,$(modules))

.PHONY: all
all: $(execs)

$(execs): $(dependencies) $(objects) sources/systemc/libraries/systemc_helpers/systemc_helpers.a
	@echo "Link files"
	$(CC) -o $@ $(objects) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(LINK_LIBPATHS) $(LINK_LIBS) -pthread

.PHONY: clean
clean:
	$(RM) $(objects) $(execs) $(dependencies)
	make clean -C source/systemc/libraries/systemc_helpers

sources/systemc/libraries/systemc_helpers/systemc_helpers.a:
	make -C source/systemc/libraries/systemc_helpers
	
#ifneq "$(MAKECMDGOALS)" "clean"
#	include $(dependencies)
#	@echo "included dependencies"
#endif

%.d: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cpp,.d,$<)

%.d: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cc,.d,$<)

#%.o: %.cpp %.cc
#	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@
