local_dir := source/systemc/modules/frontend
srcs      := chip_address.cpp sensor_module_address.cpp sensor_module.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
