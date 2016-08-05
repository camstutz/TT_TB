local_dir := source/systemc/modules/backend/trigger_tower/pattern_bank
srcs      := pattern_bank.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
