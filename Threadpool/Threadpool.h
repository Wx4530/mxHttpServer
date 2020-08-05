#pragma once
#ifndef _XNET_THREADPOOL_H_
#define _XNET_THREADPOOL_H_

#include <functional>
#include <vector>
#include <queue>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>


#include "../base/sync.h"
#include "../xnet/sysAPI/Thread.h"

namespace xnet
{
// 线程池类, 只需要提供线程数就可以创建一个线程池
// 任务队列传入
class ThreadPool
{
public:
    ThreadPool();
    ThreadPool(size_t nthreads);
    ~ThreadPool();

    // template<class F, class... Args>
    // void enqueue(F&& f, Args&&... args);
    void enqueue(std::function<void()>);

    void getStatus() const
    {
        std::cout << "workers num: " << m_workers.size() << " tasks num: " << m_tasks.size() << std::endl;
    }

    bool isClose() const
    {
        return m_bClose;
    }


private:

    xnet::Mutex m_mutex;  // 互斥锁, 用来实现任务队列访问的同步
    xnet::Cond m_cond;    // 空闲的工作线程等待在该条件变量上
    std::vector<xnet::Thread> m_workers;
    std::queue<std::function<void()> > m_tasks;
    struct timespec m_waittime;    // 工作线程最大等待时间, 默认一分钟
    bool m_bClose;     // 线程池是否关闭的标志
};

inline ThreadPool::ThreadPool()
{
    ThreadPool(8);
}
// 创建指定数目个线程
inline ThreadPool::ThreadPool(size_t nthreads)
    :   m_waittime({60, 0}),
        m_bClose(false)
{
    m_workers.reserve(nthreads);
    for(size_t i = 0; i < nthreads; ++i)
        m_workers.emplace_back(
            [this]{
                for(;;)
                {
                    std::function<void()> task;
                    
                    {
                        // 无须手动调用unlock, Locker在析构的时候会自动 调用unlock
                        xnet::Locker lock(this->m_mutex);  
                        // 如果线程池处于工作状态但是任务队列为空, 则工作线程阻塞等待任务的到来
                        while(!this->m_bClose && this->m_tasks.empty())
                        {
                            std::cout << "waitting for task" << std::endl;
                            this->m_cond.wait(this->m_mutex);
                            // this->m_cond.timewait(this->m_mutex, &m_waittime);   // 等待一定时间后返回
                        }
                        // 线程池关闭标志发送后, 退出所有空闲线程
                        if(this->m_bClose)
                        {
                            return;
                        }
                        // 接受任务队列中的任务
                        task = std::move(this->m_tasks.front());
                        this->m_tasks.pop();
                    }
                    // 处理任务
                    task();
                }
            });
}

inline void ThreadPool::enqueue(std::function<void()> task) 
{
    // std::cout<< "task in" << std::endl;
    {
        xnet::Locker lock(this->m_mutex);
        // don't allow enqueueing after stopping the pool
        if(this->m_bClose)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        this->m_tasks.emplace([task]{ task(); });
    }
    this->m_cond.signal();
}

// 回收所有线程
inline ThreadPool::~ThreadPool()
{
    {
        xnet::Locker lock(this->m_mutex);
        m_bClose = true;
    }
    std::cout << " ===========================================broadcast " << std::endl;
    m_cond.broadcast();
    // sleep(1);
    
    // pthread_mutex_destroy(m_mutex.get());
    // pthread_cond_destroy(&m_cond.get());
    int i = 0;
    for (auto thr : m_workers)
    {
        std::cout << thr.tid << " =============================join " << i++ << std::endl;
        thr.join();
    }
    std::cout << "joined all" << std::endl;
}


} // namespace xnet


#endif // !_XNET_THREADPOOL_H_