local_dir := source/systemc/modules/frontend/gbt
srcs      := gbt.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
