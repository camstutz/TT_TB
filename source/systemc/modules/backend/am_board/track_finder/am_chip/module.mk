local_dir := source/systemc/modules/backend/am_board/track_finder/am_chip
srcs      := am_chip_config.cpp am_chip.cpp am_chip_read_ctrl.cpp am_chip_write_ctrl.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
