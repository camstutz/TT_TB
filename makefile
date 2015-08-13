source-to-object = $(subst .cpp,.o,$(filter %.cpp,$1)) \
                   $(subst .cc,.o,$(filter %.cc,$1))   \
                   $(subst .c,.o,$(filter %.c,$1))
                   
subdirectory = $(patsubst %/module.mk,%,                            \
                   $(word                                           \
                       $(words &(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

MODULEDIR := source/systemc/modules
modules   := $(MODULEDIR)/hit_generator
modules   += $(MODULEDIR)/frontend $(MODULEDIR)/frontend/frontend_chip $(MODULEDIR)/frontend/data_concentrator $(MODULEDIR)/frontend/gbt
modules   += $(MODULEDIR)/backend/dtc
modules   += $(MODULEDIR)/backend $(MODULEDIR)/backend/data_organizer $(MODULEDIR)/backend/processor_organizer
modules   += $(MODULEDIR)/road_analyzer

programs  :=
sources   :=

objects      = $(call source-to-object,$(sources))
dependencies = $(subst .o,.d,$(objects))
execs        = $(addsuffix _exec, $(programs))

include_dirs := /usr/local/lib/systemc-2.3.1/include /usr/local/include/root

CC       := g++
#CFLAGS   := -Wall -W -pedantic -ggdb3 -M
CPPFLAGS := -Wall -std=c++11 $(addprefix -I,$(include_dirs))

MV  := mv -f
RM  := rm -f
SED := sed

include $(addsuffix /module.mk,$(modules))

.PHONY: all
#all: $(execs)
all: $(dependencies) $(objects)

$(execs): $(dependencies) $(objects)
	@echo "Link files"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ $(objects)

.PHONY: clean
clean:
	$(RM) $(objects) $(execs) $(dependencies)
	
ifneq "$(MAKECMDGOALS)" "clean"
	include $(dependencies)
	@echo "included dependencies"
endif

%.d: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cpp,.d,$<)

%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@
