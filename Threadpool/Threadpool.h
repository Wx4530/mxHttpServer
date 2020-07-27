/*
 * @description: 线程池1.0, 提供固定个数个线程, 
 * @author: wx
 * @github: https://github.com/Wx4530/mxHttpServer.git
 * @lastEditors: wx
 * @Date: 2020-07-27 22:31:22
 * @LastEditTime: 2020-07-27 23:06:27
 * @Copyright: 1.0
 */ 

#ifndef _XNET_THREADPOOL_H_
#define _XNET_THREADPOOL_H_

#include <functional>
#include <vector>
#include <queue>


#include "../base/sync.h"
#include "../xnet/sysAPI/Thread.h"

namespace xnet
{
// 线程池类, 只需要提供线程数就可以创建一个线程池
// 任务队列传入
class ThreadPool
{
public:
    ThreadPool(size_t nthreads);
    ~ThreadPool();

    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args);

private:
    std::vector<xnet::Thread> m_workers;
    std::queue<std::function<void()> > m_tasks;

    xnet::Mutex m_mutex;  // 互斥锁, 用来实现任务队列访问的同步
    xnet::Cond m_cond;    // 空闲的工作线程等待在该条件变量上
    struct timespec m_waittime;    // 工作线程最大等待时间, 默认一分钟
    bool m_bClose;     // 线程池是否关闭的标志
};

// 创建指定数目个线程
ThreadPool::ThreadPool(size_t nthreads)
    :   m_bClose(false),
        m_waittime({60, 0})
{
    m_workers.reserve(nthreads);
    for(size_t i = 0; i < nthreads; ++i)
        m_workers.emplace_back([this]
        {
            for(;;)
            {
                std::function<void()> task;
                {
                    xnet::Locker(this->m_mutex);  // 无须手动调用unlock, Locker在析构的时候会自动调用unlock
                    // 如果线程池处于工作状态但是任务队列为空, 则工作线程阻塞等待任务的到来
                    if(!m_bClose && m_tasks.empty())
                    {
                        this->m_cond.wait(this->m_mutex);
                        // this->m_cond.timewait(this->m_mutex, &m_waittime);   // 等待一定时间后返回
                    }
                    // 线程池关闭标志发送后, 退出所有空闲线程
                    if(m_bClose && this->m_tasks.empty())
                        return;
                    
                    // 接受任务队列中的任务
                    task = std::move(m_tasks.front());
                    m_tasks.pop();
                }
                // 处理任务
                task();
            }
        });
}

// 向工作队列中添加任务
template<class F, class... Args>
void ThreadPool::enqueue(F&& f, Args&&... args) 
{
    auto task = std::make_shared< std::function<void()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    {
        Locker(this->m_mutex);
        // don't allow enqueueing after stopping the pool
        if(m_bClose)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        m_tasks.emplace([task](){ (*task)(); });
    }
    m_cond.signal();
}

// 回收所有线程
ThreadPool::~ThreadPool()
{
    {
        Locker(this->m_mutex);
        m_bClose = true;
    }
    m_cond.broadcast();
    for(Thread &thr : m_workers)
        thr.join();
}

} // namespace xnet




#endif // !_XNET_BASE_THREADPOOL_H_