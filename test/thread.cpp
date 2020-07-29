/*
 * @Description: 
 * @Version: 1.0
 * @Autor: wx
 * @Date: 2020-07-29 17:17:00
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-07-29 21:38:22
 */ 
#include "../xnet/sysAPI/Thread.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace xnet;

int main()
{
    vector<Thread> thrs;
    for(int i = 0; i < 1000; ++i)
    {
        thrs.emplace_back([i]{ cout << "thrfunc : " << i << endl; });
        cout << thrs.back().get_tid() << endl;
    }

    // for(auto thr : thrs)
    // {
    //     pthread_join(thr.get_tid(), NULL);
    // }


    return 0;
}