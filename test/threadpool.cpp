/*
 * @Description:    
 * @Version: 1.0
 * @Autor: wx
 * @Date: 2020-07-28 10:43:48
 * @LastEditors: wx
 * @LastEditTime: 2020-07-28 17:18:45
 */ 

#include <iostream>
#include <functional>
#include <stdlib.h>     // atoi()
#include <unistd.h>     // sleep()
#include <time.h>

#include "../Threadpool/Threadpool.h"

using namespace std;
using namespace xnet;

void func(int i )
{
    usleep(1000);
    cout << "---------------------------------------------print: "  << i << endl;
}

int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        cout << "usage: threadpool_test.out nthreads ntasks" << endl;
        exit(1);
    }
    ThreadPool pool(atoi(argv[1]));
    for (size_t i = 0; i < atoi(argv[2]); ++i)
    {
        cout << " i = " << i << endl;
        pool.enqueue(std::bind(func, i));
        cout << "enqueue successed!" << endl;
        // sleep(1);
        pool.getStatus();
    }
    
    return 0;
}
