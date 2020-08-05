 #pragma once
#ifndef _XNET_THREAD_H_
#define _XNET_THREAD_H_
#include <iostream>
#include <functional>
#include <pthread.h>

#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE	  // <features.h>
#endif // _GNU_SOURCE

namespace xnet
{

typedef std::function<void ()> ThreadFunc;
namespace thread
{
struct ThreadData
{
    ThreadFunc func_;
    ThreadData(ThreadFunc func)
        : func_(std::move(func))
    { }
};

static void* start(void* obj)
{
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->func_();
  delete data;
  return NULL;
}

}   // namespace thread

// 自己的简单线程类
// 不处理返回值
// 只接受std::function<void()> 参数
// 具体参数可以通过std::bind传入
class Thread
{
public:
    // 创建线程的同时启动线程
    Thread(ThreadFunc func)
        :   joinable(true)
    {
        thread::ThreadData* data = new thread::ThreadData(func);
        pthread_create(&tid, NULL, thread::start, data);
    }

    // 不单独给出join接口, 线程对象销毁时自动join
    ~Thread()
    {
        // if(joinable)
        // {
        //     pthread_join(tid, NULL);
        // }
        // pthread_cancel(tid);
        // pthread_exit(NULL);
        std::cout << "~Thread() called" << std::endl;
    }
    
    // 设置标志位, 设置线程分离
    void detach()
    {
        joinable = false;
        pthread_detach(tid);
    }

    // 设置标志位, 等待线程结束
    void join()
    {
        if(joinable)
        {
            joinable = false;
            pthread_join(tid, NULL);
        }
    }

public:
    pthread_t tid;
    bool joinable;
};


} // namespace xnet

#endif // !_XNET_THREAD_H_