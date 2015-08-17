local_dir := source/systemc/modules/backend/am_board/track_finder/pattern_bank
srcs      := pattern_bank.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
