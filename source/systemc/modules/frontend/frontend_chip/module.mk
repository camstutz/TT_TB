local_dir := source/systemc/modules/frontend/frontend_chip
srcs      := frontend_chip.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
