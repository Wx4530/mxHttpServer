#include "Thread.h"

using namespace xnet;

// 创建线程的同时启动线程
Thread::Thread(ThreadFunc func)
    :   m_bRun(true)
{
    thread::ThreadData* data = new thread::ThreadData(func);
    Pthread_create(&m_tid, NULL, thread::start, data);
}

// 析构的时候设置线程分离, 当其完成当前任务后再销毁
Thread::~Thread()
{
    Pthread_detach(m_tid);
}

// 回收一个线程, 不回收其返回值
void Thread::join()
{
    Pthread_join(m_tid, NULL);
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