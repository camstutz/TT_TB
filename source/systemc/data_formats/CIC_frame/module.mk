local_dir := source/systemc/data_formats/CIC_frame
srcs      := CIC_frame.cpp header.cpp trailer.cpp

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
