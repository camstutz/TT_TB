local_dir := source/systemc/data_formats/gbt_link_format
srcs      := gbt_link_format.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
