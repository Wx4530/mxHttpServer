/*
 * @description: Thread类, 对pthread的简单封装
 * @author: wx
 * @github: https://github.com/Wx4530/myWebServer.git
 * @lastEditors: wx
 * @Date: 2020-07-26 22:37:41
 * @LastEditTime: 2020-07-29 23:53:19
 * @Copyright: 1.0
 */ 
#ifndef _XNET_THREAD_H_
#define _XNET_THREAD_H_

#include <functional>

#include "SysPthread.h"

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

void* start(void* obj)
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
    Thread(ThreadFunc);
    ~Thread();
    void join();
    pthread_t get_tid();
    void detach();
private:
    pthread_t m_tid;
    ThreadFunc m_func;
    bool m_bRun;
    bool m_bDetached;
};

// 创建线程的同时启动线程
Thread::Thread(ThreadFunc func)
    :   m_bRun(true),
        m_bDetached(false)
{
    thread::ThreadData* data = new thread::ThreadData(func);
    Pthread_create(&m_tid, NULL, thread::start, data);
}

// 析构的时候设置线程分离, 当其完成当前任务后再销毁
Thread::~Thread()
{
    // join();
}

// 回收一个线程, 不回收其返回值
void Thread::join()
{
    pthread_join(m_tid, NULL);
}

pthread_t Thread::get_tid()
{
    return m_tid;
}

// 由于detach两次也不会出什么问题, 因此不设置标志位
void Thread::detach()
{
    Pthread_detach(m_tid);
}

} // namespace xnet

#endif // !_XNET_THREAD_H_