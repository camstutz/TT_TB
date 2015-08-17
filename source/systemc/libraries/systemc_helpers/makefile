include_dirs := /usr/local/lib/systemc-2.3.1/include

librarypaths := /usr/local/lib/systemc-2.3.1/lib-linux64
libraries := systemc

sub_libs := sc_analyzer sc_map


##########################################################################################

LINK_LIBS     = $(addprefix -l,$(libraries))
LINK_LIBPATHS = $(addprefix -L,$(librarypaths))

CC       := g++
CPPFLAGS := -Wall -g3 -O0 -std=c++11 $(addprefix -I,$(include_dirs)) $(LINK_LIBPATHS) $(LINK_LIBS)

SUBLIBS_SRC  := $(addsuffix /src,$(sub_libs))
SOURCES      := $(foreach _LIB,$(SUBLIBS_SRC),$(wildcard $(_LIB)/*.cpp))
OBJECTS      := $(subst .cpp,.o,$(SOURCES))
DEPENDENCIES := $(subst .cpp,.d,$(SOURCES))

TESTSOURCES      := test/main.cpp test/source.cpp test/sink.cpp test/sc_delay_tb.cpp
TESTOBJECTS      := $(subst .cpp,.o,$(TESTSOURCES))
TESTDEPENDENCIES := $(subst .cpp,.d,$(TESTSOURCES))

.PHONY: all
all: systemc_helpers.a

systemc_helpers.a : $(DEPENDENCIES) $(OBJECTS)
	ar rvs libsystemc_helpers.a $(OBJECTS)

.PHONY: test
test: systemc_helpers_test

systemc_helpers_test: systemc_helpers.a $(TESTDEPENDENCIES) $(TESTOBJECTS)
	$(CC) -o $@ $(TESTOBJECTS) $(CPPFLAGS) $(TARGET_ARCH) -L. -lsystemc_helpers

%.d: %.cpp
	$(CC) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cpp,.d,$<)

%.o : %.cpp
	$(CC) $(CPPFLAGS) -MD -c $< -o $(patsubst %.cpp, %.o, $<)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDENCIES) $(TESTDEPENDENCIES) $(TESTOBJECTS)
	rm -f libsystemc_helpers.a systemc_helpers_test

ifneq "$(MAKECMDGOALS)" "clean"
	include $(DEPENDENCIES)
	@echo "included dependencies"
endif
