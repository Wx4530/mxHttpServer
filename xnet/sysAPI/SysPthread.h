/*
 * @Description: 
 * @Version: 1.0
 * @Autor: wx
 * @Date: 2020-07-28 10:43:48
 * @LastEditors: wx
 * @LastEditTime: 2020-07-28 12:55:45
 */ 
#ifndef _XNET_WRAPPTHREAD_H_
#define _XNET_WRAPPTHREAD_H_

#include <pthread.h>

// ---------------------------------DEFINES---------------------------------------------------------------
#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE	  // <features.h>
#endif // _GNU_SOURCE

/* If _GNU_SOURCE was defined by the user, turn on all the other features.  */

// --------------------------------wrappthread.c----------------------------------------------------------

/*
 * pthreads wrapper functions.
 */
namespace xnet
{
	
void Pthread_create(pthread_t *tid, const pthread_attr_t *attr,
			   void * (*func)(void *), void *arg);

// 回收指定线程, 并接收其返回值
void Pthread_join(pthread_t tid, void **status);

// 设置线程分离
void Pthread_detach(pthread_t tid);

// 向线程tid发送kill信号
// void Pthread_kill(pthread_t tid, int signo);

// 以下三个暂时不常用到
void Pthread_once(pthread_once_t *ptr, void (*func)(void));

void Pthread_key_create(pthread_key_t *key, void (*func)(void *));

void Pthread_setspecific(pthread_key_t key, const void *value);


} // namespace xnet


#endif // !_XNET_WRAPPTHREAD_H_

