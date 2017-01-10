cxx=g++
linkflag=-luuid -lpthread -o
compflag=-c -pipe -O2 -D__X64__
binpath=./BIN/

srcs=$(wildcard ./GAIA/TEST/*.cpp)
objs=$(srcs:%.cpp=%.o)

build:$(objs)
#	@echo ------begin link------ $(objs)
	$(cxx) $(objs) $(linkflag) $(binpath)gaia

$(objs):%.o:%.cpp
#	@echo ------begin compile------ $(objs)
	$(cxx) $(compflag) $< -o $@
	
.PHONY:clean
clean:
#	@echo ------begin clear------ $(objs)
	-rm $(objs)
	-rm $(binpath)gaia
