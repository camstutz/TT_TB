local_dir := source/systemc/TT_configuration
srcs      := sector_info.cpp local_module_address.cpp prbf_module_address.cpp track_trigger_config.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
