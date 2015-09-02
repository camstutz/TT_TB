local_dir := source/systemc/modules/backend/am_board/track_finder/hit_processor
srcs      := hit_processor_config.cpp hit_processor.cpp hit_processor_one_layer.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
