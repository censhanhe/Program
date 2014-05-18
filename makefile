CXX=clang++
CXXFLAGS=-pthread
BINPATH=./BIN/

all:$gaia $fsha $prom

$gaia:../Program/GAIA/TEST/t_main.cpp
	$(CXX) $(CXXFLAGS) ../Program/GAIA/TEST/t_main.cpp -o $(BINPATH)gaia

$fsha:../Program/DWARFS/FILESHARE/main.cpp
	$(CXX) $(CXXFLAGS) ../Program/DWARFS/FILESHARE/main.cpp -o $(BINPATH)fsha

$prom:../Program/PROMETHEUS/main.cpp
	$(CXX) $(CXXFLAGS) ../Program/PROMETHEUS/main.cpp -o $(BINPATH)prom



