/*
 * @description: 
 * @author: wx
 * @github: https://github.com/Wx4530/mxHttpServer.git
 * @lastEditors: wx
 * @Date: 2020-07-27 23:26:38
 * @LastEditTime: 2020-07-28 00:00:50
 * @Copyright: 1.0
 */ 

#include <stdio.h>

#include "../xnet/sysAPI/SysPthread.h"


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