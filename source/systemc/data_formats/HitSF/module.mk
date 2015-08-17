local_dir := source/systemc/data_formats/HitSF
srcs      := HitSF.cc

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
