/*
 * @description: 互斥量, 条件变量, 信号量
 * @author: wx
 * @github: https://github.com/Wx4530/myWebServer.git
 * @lastEditors: wx
 * @Date: 2020-07-26 13:34:07
 * @LastEditTime: 2020-08-04 17:27:00
 * @Copyright: 1.0
 */ 

#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include <mutex>
#include <thread>


#include "../base/noncopyable.h"
#include "../base/copyable.h"

namespace xnet
{

class Mutex : noncopyable
{
public:
    Mutex()
        :   m_mutex(PTHREAD_MUTEX_INITIALIZER)
    { }
    ~Mutex()
    {
        pthread_mutex_destroy(&m_mutex);
    }
    
    void lock()
    {
        int ret;
        if( (ret  = pthread_mutex_lock(&m_mutex)) != 0)
            printf("mutex lock failed: %s/n", strerror(ret));
    }

    void trylock()
    {
        int ret;
        if( (ret = pthread_mutex_trylock(&m_mutex)) != 0)
            printf("mutex trylock failed: %s/n", strerror(ret));
    }

    void unlock()
    {
        int ret;
        if( (ret = pthread_mutex_unlock(&m_mutex)) != 0)
            printf("mutex unlock failed: %s/n", strerror(ret));
    }

    pthread_mutex_t* get()
    {
        return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};

class Locker : noncopyable
{
public:
    Locker(Mutex& mutex) : m_mutex(&mutex) { mutex.lock(); }
    ~Locker(){ m_mutex->unlock(); }
private:
    Mutex* m_mutex;
};

class Cond : noncopyable
{
public:
    Cond()
        :   m_cond(PTHREAD_COND_INITIALIZER)
            // m_errno(0)
    { }
    ~Cond()
    {
        pthread_cond_destroy(&m_cond);
    }

    // 解锁并等待, 原子操作
    void wait(Mutex& mutex)
    {
        if( (errno = pthread_cond_wait(&m_cond, mutex.get()) != 0))
            perror("cond wait error"), exit(1);
    }
    
    // 解锁并等待, 等待一定时间后返回
    void timewait(Mutex &mutex, struct timespec* tm)
    {
        if( (errno = pthread_cond_timedwait(&m_cond, mutex.get(), tm) != 0))
            perror("cond signal error"), exit(1);
    }

    void signal()
    {
        if( (errno = pthread_cond_signal(&m_cond) != 0))
            perror("cond signal error"), exit(1);
    }

    void broadcast()
    {
        if( (errno = pthread_cond_broadcast(&m_cond) != 0))
            perror("cond signal error"), exit(1);
    }

    pthread_cond_t& get()
    {
        return m_cond;
    }
private:
    pthread_cond_t m_cond;
};

// 信号量
class Sem
{
public:
    Sem()
    {
        if (sem_init(&m_sem, 0, 0) != 0)
        {
            throw std::exception();
        }
    }
    Sem(int num)
    {
        if (sem_init(&m_sem, 0, num) != 0)
        {
            throw std::exception();
        }
    }
    ~Sem()
    {
        sem_destroy(&m_sem);
    }
    void wait()
    {
        if(sem_wait(&m_sem) == -1)
            perror("sem wait error"), throw "sem wait error";
    }
    void post()
    {
        if(sem_post(&m_sem) == -1)
            perror("sem post error"), throw "sem post error";
    }

private:
    sem_t m_sem;
};

} // namespace xnet
