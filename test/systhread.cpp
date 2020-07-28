/*
 * @description: 
 * @author: wx
 * @github: https://github.com/Wx4530/mxHttpServer.git
 * @lastEditors: wx
 * @Date: 2020-07-27 23:26:38
 * @LastEditTime: 2020-07-28 12:57:20
 * @Copyright: 1.0
 */ 

#include <stdio.h>

#include "../xnet/sysAPI/SysPthread.h"

using namespace xnet;

void* func(void *)
{
    printf("this is a threadfunc\n");
    return NULL;
}


int main()
{
    pthread_t tid;
    Pthread_create(&tid, NULL, func, NULL);

    Pthread_join(tid, NULL);

    return 0;
}