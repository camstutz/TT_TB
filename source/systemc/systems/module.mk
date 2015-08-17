local_dir := source/systemc/systems
srcs      := TT_TB_sim.cpp tt_tb.cpp tt_tb_logger.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
