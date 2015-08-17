local_dir := source/systemc/modules/backend/am_board/track_finder/road_processor
srcs      := road_processor.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
