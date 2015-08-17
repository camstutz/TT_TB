local_dir := source/systemc/data_formats/prbf
srcs      := element_type.cpp header.cpp stub_PRBF.cpp stub_type.cpp stub_PRBF0.cpp stub_PRBF1.cpp stub_PRBF2.cpp trailer.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
