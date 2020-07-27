SrcFiles=$(wildcard *.cpp)
TargetFIles=$(patsubst %.cpp,%.o,$(SrcFiles))

all : $(TargetFIles)

%.o : %.cpp
	g++ $^ -c -lpthread


clean:
	rm -f $(TargetFIles)
