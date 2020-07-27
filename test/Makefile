threadpool : threadpool.cpp ../xnet/sysAPI/Thread.o ../xnet/sysAPI/SysPthread.o
	g++ $^ -o threadpool.out -lpthread

systhread : systhread.o
	g++ $^ -lpthread -I ../xnet/sysAPI

systhread.o : systhread.cpp
	g++ systhread.cpp -c -lpthread


clean:
	rm -f *.out
	rm -f *.o
