local_dir := source/systemc/modules/backend/processor_organizer
srcs      := processor_organizer_config.cpp po_layer_splitter_config.cpp processor_organizer.cpp po_layer_splitter.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
