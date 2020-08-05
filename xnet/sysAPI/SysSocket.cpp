/*
* 错误信息暂时先输出在stdout和stderr
* 以后加入日志系统后错误信息同时写在日志中
* 最好支持异步日志功能
*/

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "SysSocket.h"
#include "error.h"

using namespace xnet;

/* include Socket */
int sys::Socket(int family, int type, int protocol)
{
	int		n;
	if ( (n = socket(family, type, protocol)) < 0)
		error_exit("socket error");
	return(n);
}
/* end Socket */

void sys::Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		error_exit("bind error");
}

/* include Listen */
void sys::Listen(int fd, int backlog)
{
	char	*ptr;

		/*4can override 2nd argument with environment variable */
	if ( (ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(fd, backlog) < 0)
		error_exit("listen error");
}
/* end Listen */

int sys::Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int ret;

again:
	if ( (ret = accept(fd, sa, salenptr)) < 0) {
		if (errno == ECONNABORTED)
			goto again;
		else
			error_exit("accept error");
	}
	return(ret);
}

void sys::Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0)
		error_exit("connect error");
}

// TODO: may not use it
void sys::Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	if (getpeername(fd, sa, salenptr) < 0)
		error_exit("getpeername error");
}

// TODO: may not use it
void sys::Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	if (getsockname(fd, sa, salenptr) < 0)
		error_exit("getsockname error");
}

// 
void sys::Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr)
{
	if (getsockopt(fd, level, optname, optval, optlenptr) < 0)
		error_exit("getsockopt error");
}

// flags defaults: 0
ssize_t sys::Recv(int fd, void *ptr, size_t nbytes, int flags)
{
	ssize_t		n;

again:
	if ( (n = recv(fd, ptr, nbytes, flags)) < 0){
		if(errno == EAGAIN)
			goto again;
		else if(errno != 104)
			error_exit("recv error");
	}
	return(n);
}

// udp may use this
ssize_t sys::Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		 struct sockaddr *sa, socklen_t *salenptr)
{
	ssize_t		n;

	if ( (n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
		error_exit("recvfrom error");
	return(n);
}


ssize_t sys::Recvmsg(int fd, struct msghdr *msg, int flags)
{
	ssize_t		n;

	if ( (n = recvmsg(fd, msg, flags)) < 0)
		error_exit("recvmsg error");
	return(n);
}



void sys::Send(int fd, const void *ptr, size_t nbytes, int flags)
{
	if (send(fd, ptr, nbytes, flags) != (ssize_t)nbytes)
		error_exit("send error");
}

void sys::Sendto(int fd, const void *ptr, size_t nbytes, int flags,
	   const struct sockaddr *sa, socklen_t salen)
{
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
		error_exit("sendto error");
}

void sys::Sendmsg(int fd, const struct msghdr *msg, int flags)
{
	unsigned int	i;
	ssize_t			nbytes;

	nbytes = 0;	/* must first figure out what return value should be */
	for (i = 0; i < msg->msg_iovlen; i++)
		nbytes += msg->msg_iov[i].iov_len;

	if (sendmsg(fd, msg, flags) != nbytes)
		error_exit("sendmsg error");
}

void sys::Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(fd, level, optname, optval, optlen) < 0)
		error_exit("setsockopt error");
}

void sys::Shutdown(int fd, int how)
{
	if (shutdown(fd, how) < 0)
		error_exit("shutdown error");
}

int sys::Sockatmark(int fd)
{
	int		n;

	if ( (n = sockatmark(fd)) < 0)
		error_exit("sockatmark error");
	return(n);
}

void sys::Socketpair(int family, int type, int protocol, int *fd)
{
	int		n;

	if ( (n = socketpair(family, type, protocol, fd)) < 0)
		error_exit("socketpair error");
}