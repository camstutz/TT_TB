local_dir := source/systemc/modules/backend/trigger_tower
srcs      := trigger_tower_address.cpp trigger_tower.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
