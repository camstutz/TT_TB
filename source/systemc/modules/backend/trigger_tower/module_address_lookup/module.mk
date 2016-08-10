local_dir := source/systemc/modules/backend/trigger_tower/module_address_lookup
srcs      := module_address_lookup.cpp module_address_lookup_config.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
