local_dir := source/systemc/libraries/CMSSW_extraction
srcs      := CMSPatternLayer.cc ComputerHough.cc Detector.cc FileEventProxy.cc FitParams.cc GradedPattern.cc
srcs      += Hit.cc HoughFitter.cc KarimakiTrackFitter.cc Ladder.cc Layer.cc libhoughCPU.cc Module.cc
srcs      += MultiDimFitData.cc Pattern.cc PatternFinder.cc PatternGenerator.cc PatternLayer.cc PatternTree.cc
srcs      += PatternTrunk.cc PrincipalFitGenerator.cc PrincipalTrackFitter.cc Sector.cc SectorTree.cc
srcs      += Segment.cc SuperStrip.cc Track.cc TrackFitter.cc

local_src := $(addprefix $(local_dir)/, $(srcs)) 
sources += $(local_src)
