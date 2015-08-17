local_dir := source/systemc/data_formats/stub
srcs      := stub.cpp stub_config.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
