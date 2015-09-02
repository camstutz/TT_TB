local_dir := source/systemc/modules/hit_generator
srcs      := hit_generator_config.cpp hit_generator.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
