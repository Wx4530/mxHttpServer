# SrcFiles=$(wildcard *.cpp)
# TargetFIles=$(patsubst %.cpp,%.o,$(SrcFiles))

all : threadpool systhread sync thread httpserver

Args= -std=c++11 -lpthread -O1 -g 
Net = ../xnet/EventLoop.o ../xnet/InetAddress.o ../xnet/Buffer.o ../xnet/sysAPI/SysSocket.o

httpserver : httpserver.o ../xnet/sysAPI/SysPthread.o $(Net) ../HttpServer/HttpServer.o
	g++ $^ -o $@.out $(Args)

threadpool : threadpool.o ../xnet/sysAPI/SysPthread.o
	g++ $^ -o $@.out $(Args)

systhread : systhread.o ../xnet/sysAPI/SysPthread.o
	g++ $^ -o $@.out $(Args)

sync : sync.cpp
	g++ $^ -o $@.out $(Args)

thread : thread.o ../xnet/sysAPI/SysPthread.o
	g++ $^ -o thread.out $(Args)

%.o : %.cpp
	g++ $^ -c -o $@ $(Args)

clean:
	rm -f *.out
	rm -f %.o
