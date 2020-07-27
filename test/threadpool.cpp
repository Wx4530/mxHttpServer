
#include <iostream>

#include "../Threadpool/Threadpool.h"

using namespace std;
using namespace xnet;

void func(int i)
{
    cout << "print: " << i << endl;
}

int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        cout << "usage: threadpool_test.out nthreads ntasks" << endl;
    }
    ThreadPool pool(atoi(argv[1]));

    for (size_t i = 0; i < atoi(argv[2]); i++)
    {
        pool.enqueue(func, i);
    }
    

    return 0;
}
