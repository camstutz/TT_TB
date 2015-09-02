local_dir := source/systemc/modules/backend/dtc
srcs      := dtc_type_config.cpp dtc_config.cpp dtc.cpp dtc_input_unit.cpp dtc_output_unit.cpp dtc_controller.cpp dtc_buffer_element.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
