local_dir := source/systemc/modules/frontend
srcs      := sensor_module.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
