local_dir := source/systemc/systems
srcs      := tt_tb_logger.cpp
sim_srcs  := tt_tb.cpp TT_TB_sim.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)

local_sim_src := $(addprefix $(local_dir)/, $(sim_srcs)) 
sim_sources += $(local_sim_src)
