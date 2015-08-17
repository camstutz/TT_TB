local_dir := source/systemc/data_formats/hit_file
srcs      := hit.cpp hit_file.cpp hit_value.cpp hit_value_cbc.cpp hit_value_mpa.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
