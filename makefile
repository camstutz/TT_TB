OPATH = obj
INCPATHS = -I/usr/local/lib/systemc-2.3.1/include -I/usr/local/include/root
CC = g++
CFLAGS     = -c -g3 -Wall -std=c++11 $(INCPATHS) -o $(OPATH)/$@
CFLAGS_MOD = -c -g3 -Wall -std=c++11 $(INCPATHS) -o $@
TARGET = simF_TT

MPATH = source/systemc/modules
FEPATH = $(MPATH)/frontend
BEPATH = $(MPATH)/backend

SYSTEMCLIBPATH = /usr/local/lib/systemc-2.3.1/lib-linux64
ROOTLIBPATH = /usr/local/lib/root
LIBPATHS = -L$(SYSTEMCLIBPATH) -L$(ROOTLIBPATH)

BOOSTLIBS = -lboost_system -lboost_thread -lboost_serialization -lboost_iostreams -lboost_log -lpthread
ROOTLIBS = -lHist -lGpad -lThread -lPhysics -lGraf -lGraf3d -lMatrix -lRIO -lNet -lCore -lTree
LIBS = -lsystemc $(BOOSTLIBS) $(ROOTLIBS)

SC_HELPER_PATH = source/systemc/libraries/systemc_helpers

all: $(TARGET)	

$(TARGET): $(OPATH)/TT_TB_sim.o sc_map_lib sc_analyzer_lib
	$(CC) -o $(TARGET) $(SC_HELPER_PATH)/obj/sc_analyzer.o $(SC_HELPER_PATH)/obj/sc_map_key.o $(SC_HELPER_PATH)/obj/sc_map_regular_key.o \
$(SC_HELPER_PATH)/obj/sc_map_linear_key.o $(SC_HELPER_PATH)/obj/sc_map_linear_range.o \
$(SC_HELPER_PATH)/obj/sc_map_square_key.o $(SC_HELPER_PATH)/obj/sc_map_square_range.o \
$(SC_HELPER_PATH)/obj/sc_map_cube_key.o $(SC_HELPER_PATH)/obj/sc_map_cube_range.o \
$(SC_HELPER_PATH)/obj/sc_map_4d_key.o $(SC_HELPER_PATH)/obj/sc_map_4d_range.o \
$(SC_HELPER_PATH)/obj/sc_analyzer.o $(OPATH)/tt_tb_logger.o \
$(OPATH)/HitSF.o $(OPATH)/header.o $(OPATH)/trailer.o $(OPATH)/element_type.o \
$(OPATH)/stub.o $(OPATH)/stub_config.o $(OPATH)/CIC_frame.o $(OPATH)/CIC_header.o $(OPATH)/CIC_trailer.o \
$(OPATH)/stub_type.o $(OPATH)/stub_PRBF.o $(OPATH)/stub_PRBF0.o $(OPATH)/stub_PRBF1.o $(OPATH)/stub_PRBF2.o \
$(OPATH)/gbt_link_format.o \
$(OPATH)/hit_generator.o $(OPATH)/road_analyzer.o $(OPATH)/trigger_tower.o $(OPATH)/tt_tb.o \
$(OPATH)/sensor_module.o $(OPATH)/frontend_chip.o $(OPATH)/data_concentrator.o $(OPATH)/gbt.o \
$(OPATH)/am_board.o $(OPATH)/am_input_module.o $(OPATH)/am_input_module_one_layer.o $(OPATH)/am_input_module_ctrl.o \
$(OPATH)/track_finder.o $(OPATH)/am_chip.o $(OPATH)/am_chip_read_ctrl.o $(OPATH)/am_chip_write_ctrl.o $(OPATH)/hit_buffer.o  $(OPATH)/pattern_bank.o $(OPATH)/pattern_memory.o $(OPATH)/road_processor.o \
$(OPATH)/dtc.o $(OPATH)/data_organizer.o $(OPATH)/processor_organizer.o  \
TT_TB_sim.o \
$(LIBPATHS) $(LIBS)

#$(TARGET): $(OPATH)/TT_TB_sim.o sc_map_lib sc_analyzer_lib
#	$(CC) -o $(TARGET) $(SC_HELPER_PATH)/obj/*.o obj/*.o $(LIBPATHS) $(LIBS)

$(OPATH)/TT_TB_sim.o: $(OPATH)/tt_tb.o
	$(CC) $(CFLAGS_MOD) source/systemc/systems/TT_TB_sim.cpp

# Track trigger environment -----------------------------------------

$(OPATH)/tt_tb.o: source/systemc/systems/tt_tb.cpp source/systemc/systems/tt_tb.hpp \
                  $(OPATH)/hit_generator.o $(OPATH)/sensor_module.o $(OPATH)/dtc.o $(OPATH)/trigger_tower.o $(OPATH)/road_analyzer.o $(OPATH)/tt_tb_logger.o
	$(CC) $(CFLAGS_MOD) source/systemc/systems/tt_tb.cpp

$(OPATH)/tt_tb_logger.o: source/systemc/systems/tt_tb_logger.cpp source/systemc/systems/tt_tb_logger.hpp
	$(CC) $(CFLAGS_MOD) source/systemc/systems/tt_tb_logger.cpp

# Hit generator ------------------------------------------------------

$(OPATH)/hit_generator.o: $(MPATH)/hit_generator/hit_generator.cpp $(MPATH)/hit_generator/hit_generator.hpp $(MPATH)/hit_generator/hit_generator_config.hpp \
                          $(OPATH)/HitSF.o $(OPATH)/stub.o
	$(CC) $(CFLAGS_MOD) $(MPATH)/hit_generator/hit_generator.cpp

# Sensor module -------------------------------------------------------

$(OPATH)/sensor_module.o: $(MPATH)/frontend/sensor_module.cpp $(MPATH)/frontend/sensor_module.hpp $(MPATH)/frontend/sensor_module_config.hpp $(MPATH)/frontend/sensor_module_type_config.hpp \
                          $(OPATH)/frontend_chip.o $(OPATH)/data_concentrator.o $(OPATH)/gbt.o
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/sensor_module.cpp

$(OPATH)/frontend_chip.o: $(MPATH)/frontend/frontend_chip.cpp $(MPATH)/frontend/frontend_chip.hpp $(MPATH)/frontend/frontend_chip_config.hpp $(MPATH)/frontend/fe_chip_output_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/frontend_chip.cpp

$(OPATH)/data_concentrator.o: $(MPATH)/frontend/data_concentrator.cpp $(MPATH)/frontend/data_concentrator.hpp $(MPATH)/frontend/data_concentrator_config.hpp \
                              $(OPATH)/CIC_frame.o
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/data_concentrator.cpp

$(OPATH)/gbt.o: $(MPATH)/frontend/gbt.cpp $(MPATH)/frontend/gbt.hpp $(MPATH)/frontend/gbt_config.hpp \
                $(OPATH)/gbt_link_format.o
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/gbt.cpp

# DTC -------------------------------------------------------------------

$(OPATH)/dtc.o: $(MPATH)/backend/dtc/dtc.cpp $(MPATH)/backend/dtc/dtc.hpp $(MPATH)/backend/dtc/dtc_config.hpp \
                $(OPATH)/dtc_controller.o $(OPATH)/dtc_buffer_element.o $(OPATH)/dtc_input_unit.o $(OPATH)/dtc_output_unit.o
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/gbt.cpp

$(OPATH)/dtc_controller.o: $(MPATH)/backend/dtc/dtc_controller.cpp $(MPATH)/backend/dtc/dtc_controller.hpp $(MPATH)/backend/dtc/dtc_controller_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_controller.cpp

$(OPATH)/dtc_buffer_element.o: $(MPATH)/backend/dtc/dtc_buffer_element.cpp $(MPATH)/backend/dtc/dtc_buffer_element.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_buffer_element.cpp

$(OPATH)/dtc_input_unit.o: $(MPATH)/backend/dtc/dtc_input_unit.cpp $(MPATH)/backend/dtc/dtc_input_unit.hpp $(MPATH)/backend/dtc/dtc_input_unit_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_input_unit.cpp

$(OPATH)/dtc_output_unit.o: $(MPATH)/backend/dtc/dtc_output_unit.cpp $(MPATH)/backend/dtc/dtc_output_unit.hpp $(MPATH)/backend/dtc/dtc_output_unit_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_output_unit.cpp

# Trigger Tower ---------------------------------------------------------

$(OPATH)/trigger_tower.o: $(BEPATH)/trigger_tower.cpp $(BEPATH)/trigger_tower.hpp $(BEPATH)/trigger_tower_config.hpp \
                          $(OPATH)/data_organizer.o $(OPATH)/processor_organizer.o $(OPATH)/am_board.o \
                          $(OPATH)/stub_PRBF0.o $(OPATH)/stub_PRBF1.o $(OPATH)/stub_PRBF2.o
	$(CC) $(CFLAGS_MOD) $(BEPATH)/trigger_tower.cpp

# Data Organizer --------------------------------------------------------

DOPATH = $(BEPATH)/data_organizer
BECOMMON = $(BEPATH)/common/bx_stub_buffer.hpp $(BEPATH)/common/input_collector.hpp $(BEPATH)/common/input_collector_config.hpp $(BEPATH)/common/time_demux.hpp $(BEPATH)/common/time_demux_config.hpp

$(OPATH)/data_organizer.o: $(DOPATH)/data_organizer.cpp $(DOPATH)/data_organizer.hpp $(DOPATH)/data_organizer_config.hpp $(BECOMMON)
	$(CC) $(CFLAGS_MOD) $(DOPATH)/data_organizer.cpp

# Processor Organizer ---------------------------------------------------

POPATH = $(BEPATH)/processor_organizer

$(OPATH)/processor_organizer.o: $(POPATH)/processor_organizer.cpp $(POPATH)/processor_organizer.hpp $(POPATH)/processor_organizer_config.hpp $(BECOMMON)
	$(CC) $(CFLAGS_MOD) $(POPATH)/processor_organizer.cpp

# AM Board --------------------------------------------------------------

AMBPATH = $(BEPATH)/am_board

$(OPATH)/am_board.o: $(AMBPATH)/am_board.cpp $(AMBPATH)/am_board.hpp $(AMBPATH)/am_board_config.hpp \
                     $(OPATH)/am_input_module.o $(OPATH)/track_finder.o
	$(CC) $(CFLAGS_MOD) $(AMBPATH)/am_board.cpp

# AM Input Module -------------------------------------------------------

AMBINPATH = $(AMBPATH)/am_input_module

$(OPATH)/am_input_module.o: $(AMBINPATH)/am_input_module.cpp $(AMBINPATH)/am_input_module.hpp $(AMBINPATH)/am_input_module_config.hpp \
                            $(OPATH)/am_input_module_one_layer.o $(OPATH)/am_input_module_ctrl.o
	$(CC) $(CFLAGS_MOD) $(AMBINPATH)/am_input_module.cpp
                            
$(OPATH)/am_input_module_one_layer.o: $(AMBINPATH)/am_input_module_one_layer.cpp $(AMBINPATH)/am_input_module_one_layer.hpp
	$(CC) $(CFLAGS_MOD) $(AMBINPATH)/am_input_module_one_layer.cpp
                            
$(OPATH)/am_input_module_ctrl.o: $(AMBINPATH)/am_input_module_ctrl.cpp $(AMBINPATH)/am_input_module_ctrl.hpp $(AMBINPATH)/am_input_module_ctrl_config.hpp
	$(CC) $(CFLAGS_MOD) $(AMBINPATH)/am_input_module_ctrl.cpp

# Track Finder ----------------------------------------------------------

TFPATH = $(AMBPATH)/track_finder

$(OPATH)/track_finder.o: $(TFPATH)/track_finder.cpp $(TFPATH)/track_finder.hpp $(TFPATH)/track_finder_config.hpp \
                         $(OPATH)/am_chip.o $(OPATH)/hit_buffer.o  $(OPATH)/pattern_bank.o $(OPATH)/pattern_memory.o $(OPATH)/road_processor.o
#$(OPATH)/hit_processor.o
	$(CC) $(CFLAGS_MOD) $(TFPATH)/track_finder.cpp

# AM Chip ---------------------------------------------------------------

AMCHPATH = $(TFPATH)/am_chip

$(OPATH)/am_chip.o: $(AMCHPATH)/am_chip.cpp $(AMCHPATH)/am_chip.hpp $(AMCHPATH)/am_chip_config.hpp \
                    $(OPATH)/am_chip_read_ctrl.o $(OPATH)/am_chip_write_ctrl.o
	$(CC) $(CFLAGS_MOD) $(AMCHPATH)/am_chip.cpp

$(OPATH)/am_chip_read_ctrl.o: $(AMCHPATH)/am_chip_read_ctrl.cpp $(AMCHPATH)/am_chip_read_ctrl.hpp
	$(CC) $(CFLAGS_MOD) $(AMCHPATH)/am_chip_read_ctrl.cpp

$(OPATH)/am_chip_write_ctrl.o: $(AMCHPATH)/am_chip_write_ctrl.cpp $(AMCHPATH)/am_chip_write_ctrl.hpp $(AMCHPATH)/am_chip_write_ctrl_config.hpp
	$(CC) $(CFLAGS_MOD) $(AMCHPATH)/am_chip_write_ctrl.cpp

# Hit buffer ------------------------------------------------------------

HBPATH = $(TFPATH)/hit_buffer

$(OPATH)/hit_buffer.o: $(HBPATH)/hit_buffer.cpp $(HBPATH)/hit_buffer.hpp $(HBPATH)/hit_buffer_config.hpp \
                       $(OPATH)/hit_buffer_output_ctrl.o $(OPATH)/hit_buffer_write_ctrl.o $(OPATH)/hit_buffer_lookup_ctrl.o
	$(CC) $(CFLAGS_MOD) $(HBPATH)/hit_buffer.cpp

$(OPATH)/hit_buffer_output_ctrl.o: $(HBPATH)/hit_buffer_output_ctrl.cpp $(HBPATH)/hit_buffer_output_ctrl.hpp $(HBPATH)/hit_buffer_output_ctrl_config.hpp
	$(CC) $(CFLAGS_MOD) $(HBPATH)/hit_buffer_output_ctrl.cpp

$(OPATH)/hit_buffer_write_ctrl.o: $(HBPATH)/hit_buffer_write_ctrl.cpp $(HBPATH)/hit_buffer_write_ctrl.hpp $(HBPATH)/hit_buffer_write_ctrl_config.hpp
	$(CC) $(CFLAGS_MOD) $(HBPATH)/hit_buffer_write_ctrl.cpp

$(OPATH)/hit_buffer_lookup_ctrl.o: $(HBPATH)/hit_buffer_lookup_ctrl.cpp $(HBPATH)/hit_buffer_lookup_ctrl.hpp $(HBPATH)/hit_buffer_lookup_ctrl_config.hpp
	$(CC) $(CFLAGS_MOD) $(HBPATH)/hit_buffer_lookup_ctrl.cpp

# Hit processor ---------------------------------------------------------

HPPATH = $(TFPATH)/hit_processor

$(OPATH)/hit_processor.o: $(HPPATH)/hit_processor.cpp $(HPPATH)/hit_processor.hpp $(HPPATH)/hit_processor_config.hpp \
                          $(OPATH)/hit_processor_one_layer.o
	$(CC) $(CFLAGS_MOD) $(HPPATH)/hit_processor.cpp

$(OPATH)/hit_processor_one_layer.o: $(HPPATH)/hit_processor_one_layer $(HPPATH)/hit_processor_one_layer.hpp
	$(CC) $(CFLAGS_MOD) $(HPPATH)/hit_processor_one_layer.cpp

# Pattern Bank ----------------------------------------------------------

PBPATH = $(TFPATH)/pattern_bank

$(OPATH)/pattern_bank.o: $(PBPATH)/pattern_bank.cpp $(PBPATH)/pattern_bank.hpp
	$(CC) $(CFLAGS_MOD) $(PBPATH)/pattern_bank.cpp

# Pattern Memory --------------------------------------------------------

PMPATH = $(TFPATH)/pattern_memory

$(OPATH)/pattern_memory.o: $(PMPATH)/pattern_memory.cpp $(PMPATH)/pattern_memory.hpp $(PMPATH)/pattern_memory_config.hpp
	$(CC) $(CFLAGS_MOD) $(PMPATH)/pattern_memory.cpp


# Road processor --------------------------------------------------------

RPPATH = $(TFPATH)/road_processor

$(OPATH)/road_processor.o: $(RPPATH)/road_processor.cpp $(RPPATH)/road_processor.hpp $(RPPATH)/road_processor_config.hpp
	$(CC) $(CFLAGS_MOD) $(RPPATH)/road_processor.cpp

# Road analyzer ---------------------------------------------------------

RAPATH = $(MPATH)/road_analyzer

$(OPATH)/road_analyzer.o: $(RAPATH)/road_analyzer.cpp $(RAPATH)/road_analyzer.hpp
	$(CC) $(CFLAGS_MOD) $(RAPATH)/road_analyzer.cpp

# Data formats -----------------------------------------------------------

DFPATH = source/systemc/data_formats

$(OPATH)/HitSF.o: $(DFPATH)/HitSF/HitSF.cc $(DFPATH)/HitSF/HitSF.h
	$(CC) $(CFLAGS_MOD) $(DFPATH)/HitSF/HitSF.cc

$(OPATH)/stub.o: $(DFPATH)/stub/stub.cpp $(DFPATH)/stub/stub.hpp \
                 $(OPATH)/stub_config.o
	$(CC) $(CFLAGS_MOD) $(DFPATH)/stub/stub.cpp

$(OPATH)/stub_config.o: $(DFPATH)/stub/stub_config.cpp $(DFPATH)/stub/stub_config.hpp
	$(CC) $(CFLAGS_MOD) $(DFPATH)/stub/stub_config.cpp

$(OPATH)/gbt_link_format.o: $(DFPATH)/gbt_link_format/gbt_link_format.cpp $(DFPATH)/gbt_link_format/gbt_link_format.hpp
	$(CC) $(CFLAGS_MOD) $(DFPATH)/gbt_link_format/gbt_link_format.cpp

CICPATH = $(DFPATH)/CIC_frame

$(OPATH)/CIC_frame.o: $(CICPATH)/CIC_frame.cpp $(CICPATH)/CIC_frame.hpp \
                      $(OPATH)/CIC_header.o $(OPATH)/CIC_trailer.o
	$(CC) $(CFLAGS_MOD) $(CICPATH)/CIC_frame.cpp

$(OPATH)/CIC_header.o: $(CICPATH)/header.cpp $(CICPATH)/header.hpp
	$(CC) $(CFLAGS_MOD) $(CICPATH)/header.cpp

$(OPATH)/CIC_trailer.o: $(CICPATH)/trailer.cpp $(CICPATH)/trailer.hpp
	$(CC) $(CFLAGS_MOD) $(CICPATH)/trailer.cpp

PRBFPATH = $(DFPATH)/prbf

$(OPATH)/stub_PRBF0.o: $(PRBFPATH)/stub_PRBF0.cpp $(PRBFPATH)/stub_PRBF0.hpp $(OPATH)/stub_PRBF.o
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/stub_PRBF0.cpp

$(OPATH)/stub_PRBF1.o: $(PRBFPATH)/stub_PRBF1.cpp $(PRBFPATH)/stub_PRBF1.hpp $(OPATH)/stub_PRBF.o
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/stub_PRBF1.cpp

$(OPATH)/stub_PRBF2.o: $(PRBFPATH)/stub_PRBF2.cpp $(PRBFPATH)/stub_PRBF2.hpp $(OPATH)/stub_PRBF.o
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/stub_PRBF2.cpp

$(OPATH)/stub_PRBF.o: $(PRBFPATH)/stub_PRBF.cpp $(PRBFPATH)/stub_PRBF.hpp $(OPATH)/header.o $(OPATH)/trailer.o $(OPATH)/element_type.o $(OPATH)/stub_type.o
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/stub_PRBF.cpp

$(OPATH)/header.o: $(PRBFPATH)/header.cpp $(PRBFPATH)/header.hpp
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/header.cpp

$(OPATH)/trailer.o: $(PRBFPATH)/trailer.cpp $(PRBFPATH)/trailer.hpp
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/trailer.cpp

$(OPATH)/element_type.o: $(PRBFPATH)/element_type.cpp $(PRBFPATH)/element_type.hpp
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/element_type.cpp

$(OPATH)/stub_type.o: $(PRBFPATH)/stub_type.cpp $(PRBFPATH)/stub_type.hpp
	$(CC) $(CFLAGS_MOD) $(PRBFPATH)/stub_type.cpp

# Libraries --------------------------------------------------------------

sc_map_lib: 
	cd source/systemc/libraries/systemc_helpers && make sc_map

sc_analyzer_lib: 
	cd source/systemc/libraries/systemc_helpers && make sc_analyzer

# other targets ---------------------------------------------------------

.PHONY: clean

clean:
	rm -f $(OPATH)/*.o *~ $(TARGET)
	cd source/systemc/libraries/systemc_helpers && make clean
