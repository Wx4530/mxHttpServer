/*
 * @Description: 
 * @Version: 1.0
 * @Autor: wx
 * @Date: 2020-07-28 16:05:25
 * @LastEditors: wx
 * @LastEditTime: 2020-07-28 16:20:48
 */ 
#include "../base/sync.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace xnet;

struct Data
{
    int i;
    pthread_mutex_t mtx;
    pthread_cond_t cond;
}data = {0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

void* func(void* arg)
{
    {
        pthread_mutex_lock(&data.mtx);
        pthread_cond_wait(&data.cond, &data.mtx);
        pthread_detach(pthread_self());
        return NULL;
    }
    return NULL;
}


int main()
{
    pthread_t tid[10];
    for(int i = 0; i < 10; ++i)
    {
        pthread_create(&tid[i], NULL, func, NULL);
    }

    pthread_cond_broadcast(&data.cond);

    return 0;
}