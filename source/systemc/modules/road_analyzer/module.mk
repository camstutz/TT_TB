local_dir := source/systemc/modules/road_analyzer
srcs      := road_analyzer.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
