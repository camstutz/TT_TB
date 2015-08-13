local_dir := source/systemc/modules/frontend/data_concentrator
srcs      := data_concentrator.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
