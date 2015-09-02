local_dir := source/systemc/modules/backend/am_board/track_finder/hit_buffer
srcs      := hit_buffer_config.cpp hit_buffer.cpp hit_buffer_lookup_ctrl.cpp hit_buffer_output_ctrl.cpp hit_buffer_write_ctrl.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
