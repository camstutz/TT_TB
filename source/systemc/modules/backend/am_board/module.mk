local_dir := source/systemc/modules/backend/am_board
srcs      := am_board.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
