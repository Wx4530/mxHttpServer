all : threadpool systhread sync

threadpool : threadpool.o ../xnet/sysAPI/Thread.o ../xnet/sysAPI/SysPthread.o
	g++ $^ -o threadpool.out -lpthread -std=c++11

systhread : systhread.o ../xnet/sysAPI/SysPthread.o
	g++ $^ -o systhread.out -lpthread

sync : sync.cpp
	g++ sync.cpp -o sync.out -lpthread -std=c++11 -O1

%.o : %.cpp
	g++ $^ -c -o $@ -lpthread -std=c++11 -O1

clean:
	rm -f *.out
	rm -f *.o
