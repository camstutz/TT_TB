local_dir := source/systemc/modules/backend/am_board/am_input_module
srcs      := am_input_module_config.cpp am_input_module.cpp am_input_module_one_layer.cpp am_input_module_ctrl.cpp 

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
