OPATH = obj
HPATHS = -I/usr/local/lib/systemc-2.3.1/include -I/usr/local/include/root
CC = gcc
CFLAGS     = -c -g3 -Wall -std=c++11 $(HPATHS) -o $(OPATH)/$@
CFLAGS_MOD = -c -g3 -Wall $(HPATHS) -o $@
TARGET = simF_TT

MPATH = source/systemc/modules

all: $(TARGET)

$(TARGET): $(OPATH)/hit_generator.o $(OPATH)/sensor_module.o $(OPATH)/dtc.o
	$(CC) $(CFLAGS) source/systemc/systems/TT_TB_sim.cpp

# Hit generator ------------------------------------------------------

$(OPATH)/hit_generator.o:
	$(CC) $(CFLAGS_MOD) $(MPATH)/hit_generator/hit_generator.cpp

# Sensor module -------------------------------------------------------

$(OPATH)/sensor_module.o: $(MPATH)/frontend/sensor_module.cpp $(MPATH)/frontend/sensor_module.hpp $(MPATH)/frontend/sensor_module_config.hpp $(MPATH)/frontend/sensor_module_type_config.hpp $(OPATH)/frontend_chip.o $(OPATH)/data_concentrator.o $(OPATH)/gbt.o
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/sensor_module.cpp

$(OPATH)/frontend_chip.o: $(MPATH)/frontend/frontend_chip.cpp $(MPATH)/frontend/frontend_chip.hpp $(MPATH)/frontend/frontend_chip_config.hpp $(MPATH)/frontend/fe_chip_output_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/frontend_chip.cpp

$(OPATH)/data_concentrator.o: $(MPATH)/frontend/data_concentrator.cpp $(MPATH)/frontend/data_concentrator.hpp $(MPATH)/frontend/data_concentrator_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/data_concentrator.cpp

$(OPATH)/gbt.o: $(MPATH)/frontend/gbt.cpp $(MPATH)/frontend/gbt.hpp $(MPATH)/frontend/gbt_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/gbt.cpp

# DTC -------------------------------------------------------------------

$(OPATH)/dtc.o: $(MPATH)/backend/dtc/dtc.cpp $(MPATH)/backend/dtc/dtc.hpp $(MPATH)/backend/dtc/dtc_config.hpp $(OPATH)/dtc_controller.o $(OPATH)/dtc_buffer_element.o $(OPATH)/dtc_input_unit.o $(OPATH)/dtc_output_unit.o
	$(CC) $(CFLAGS_MOD) $(MPATH)/frontend/gbt.cpp

$(OPATH)/dtc_controller.o: $(MPATH)/backend/dtc/dtc_controller.cpp $(MPATH)/backend/dtc/dtc_controller.hpp $(MPATH)/backend/dtc/dtc_controller_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_controller.cpp

$(OPATH)/dtc_buffer_element.o: $(MPATH)/backend/dtc/dtc_buffer_element.cpp $(MPATH)/backend/dtc/dtc_buffer_element.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_buffer_element.cpp

$(OPATH)/dtc_input_unit.o: $(MPATH)/backend/dtc/dtc_input_unit.cpp $(MPATH)/backend/dtc/dtc_input_unit.hpp $(MPATH)/backend/dtc/dtc_input_unit_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_input_unit.cpp

$(OPATH)/dtc_output_unit.o: $(MPATH)/backend/dtc/dtc_output_unit.cpp $(MPATH)/backend/dtc/dtc_output_unit.hpp $(MPATH)/backend/dtc/dtc_output_unit_config.hpp
	$(CC) $(CFLAGS_MOD) $(MPATH)/backend/dtc/dtc_output_unit.cpp

# other targets

.PHONY: clean

clean:
	rm -f $(OPATH)/*.o *~ $(TARGET)
