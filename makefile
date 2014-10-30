cxx=g++
linkflag=-luuid -lpthread -o
compflag=-c -Wall
binpath=./BIN/

srcs=$(wildcard ./GAIA/TEST/*.cpp)
objs=$(srcs:%.cpp=%.o)

build:$(objs)
	@echo ------print comment------ $(objs)
	$(cxx) $(objs) $(linkflag) $(binpath)gaia

$(objs):%.o:%.cpp
	$(cxx) $(compflag) $<

.PHONY:clean
clean:
	-rm $(binpath)gaia $(objs)
