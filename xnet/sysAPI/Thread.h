/*
 * @description: Thread类, 对pthread的简单封装
 * @author: wx
 * @github: https://github.com/Wx4530/myWebServer.git
 * @lastEditors: wx
 * @Date: 2020-07-26 22:37:41
 * @LastEditTime: 2020-07-27 23:18:05
 * @Copyright: 1.0
 */ 
#ifndef _XNET_THREAD_H
#define _XNET_THREAD_H

#include <functional>

#include "SysPthread.h"

namespace xnet
{

namespace thread
{
struct ThreadData
{
    std::function<void ()> func_;
    ThreadData(std::function<void ()> func)
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
    typedef std::function<void ()> ThreadFunc;
    Thread(ThreadFunc);
    ~Thread();
    void join();
    pthread_t get_tid();
    void detach();
private:
    pthread_t m_tid;
    ThreadFunc m_func;
    bool m_bRun;
};



} // namespace xnet

#endif // !_XNET_THREAD_H