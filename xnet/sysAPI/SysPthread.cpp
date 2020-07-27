/*
 * pthreads wrapper functions.
 */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SysPthread.h"

void error_exit(const char *desp)
{
    perror(desp);
    exit(1);
}

void
Pthread_create(pthread_t *tid, const pthread_attr_t *attr,
			   void * (*func)(void *), void *arg)
{
	int		n;

	if ( (n = pthread_create(tid, attr, func, arg)) == 0)
		return;
	errno = n;
	error_exit("pthread_create error");
}

void
Pthread_join(pthread_t tid, void **status)
{
	int		n;

	if ( (n = pthread_join(tid, status)) == 0)
		return;
	errno = n;
	error_exit("pthread_join error");
}

void
Pthread_detach(pthread_t tid)
{
	int		n;

	if ( (n = pthread_detach(tid)) == 0)
		return;
	errno = n;
	error_exit("pthread_detach error");
}

// void
// Pthread_kill(pthread_t tid, int signo)
// {
// 	int		n;

// 	if ( (n = pthread_kill(tid, signo)) == 0)
// 		return;
// 	errno = n;
// 	error_exit("pthread_kill error");
// }

void
Pthread_once(pthread_once_t *ptr, void (*func)(void))
{
	int		n;

	if ( (n = pthread_once(ptr, func)) == 0)
		return;
	errno = n;
	error_exit("pthread_once error");
}

void
Pthread_key_create(pthread_key_t *key, void (*func)(void *))
{
	int		n;

	if ( (n = pthread_key_create(key, func)) == 0)
		return;
	errno = n;
	error_exit("pthread_key_create error");
}

void
Pthread_setspecific(pthread_key_t key, const void *value)
{
	int		n;

	if ( (n = pthread_setspecific(key, value)) == 0)
		return;
	errno = n;
	error_exit("pthread_setspecific error");
}
