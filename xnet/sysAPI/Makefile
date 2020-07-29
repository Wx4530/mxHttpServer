SrcFiles=$(wildcard *.cpp)
TargetFIles=$(patsubst %.cpp,%.o,$(SrcFiles))

all : $(TargetFIles)

%.o : %.cpp
	g++ $^ -c -g -lpthread -std=c++11


clean:
	rm -f $(TargetFIles)
