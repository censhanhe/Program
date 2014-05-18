CXX=clang++
CXXFLAGS=-pthread
BINPATH=./BIN/

all:gaia dwarfs prom fsha

gaia:./GAIA/TEST/t_main.cpp
	$(CXX) $(CXXFLAGS) ./GAIA/TEST/t_main.cpp -o $(BINPATH)gaia

dwarfs:./DWARFS/TEST/t_main.cpp
	$(CXX) $(CXXFLAGS) ./DWARFS/TEST/t_main.cpp -o $(BINPATH)dwarfs

prom:./PROMETHEUS/main.cpp
	$(CXX) $(CXXFLAGS) ./PROMETHEUS/main.cpp -o $(BINPATH)prom

fsha:./DWARFS/FILESHARE/main.cpp
	$(CXX) $(CXXFLAGS) ./DWARFS/FILESHARE/main.cpp -o $(BINPATH)fsha




