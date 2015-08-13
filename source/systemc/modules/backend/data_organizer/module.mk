local_dir := source/systemc/modules/backend/data_organizer
srcs      := data_organizer.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
