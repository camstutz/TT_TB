local_dir := source/systemc/modules/backend/am_board/track_finder
srcs      := track_finder_config.cpp track_finder.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
