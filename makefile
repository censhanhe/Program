cxx=g++
linkflag=-luuid -lpthread -o
compflag=-c -Wall -Werror
binpath=./BIN/

srcs=$(wildcard ./GAIA/TEST/*.cpp)
objs=$(srcs:%.cpp=%.o)
pchh=./GAIA/TEST/preheader.h
pch=./GAIA/TEST/preheader.h.gch
pchflag=-Winvalid-pch

build:$(objs)
#	@echo ------begin link------ $(objs)
	$(cxx) $(objs) $(linkflag) $(binpath)gaia

$(objs):%.o:%.cpp $(pch)
#	@echo ------begin compile------ $(objs)
	$(cxx) $(compflag) $(pchflag) $< -o $@
	
$(pch):$(pchh)
	$(cxx) -x c++-header $(compflag) $(pchh) -o $(pch)

.PHONY:clean
clean:
#	@echo ------begin clear------ $(objs)
	-rm $(objs)
	-rm $(pch)
	-rm $(binpath)gaia
