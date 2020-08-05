#ifndef _XNET_NET_SYSSOCKET_H_
#define _XNET_NET_SYSSOCKET_H_


#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace xnet
{ 
namespace sys
{

// #define	LISTENQ		1024	/* 2nd argument to listen() */

// /* Miscellaneous constants */
// #define	MAXLINE		4096	/* max text line length */
// #define	BUFFSIZE	8192	/* buffer size for reads and writes */

// /* Define some port number that can be used for our examples */
// #define	SERV_PORT		 8080			/* TCP and UDP */
// #define	SERV_PORT_STR	"8080"			/* TCP and UDP */

// /* Following shortens all the typecasts of pointer arguments: */
// #define	SA	struct sockaddr
// #define SEPV struct epoll_event


/* include Socket */
int Socket(int family, int type, int protocol);
/* end Socket */

void Bind(int fd, const struct sockaddr *sa, socklen_t salen);

/* include Listen */
void Listen(int fd, int backlog); 
/* end Listen */

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Connect(int fd, const struct sockaddr *sa, socklen_t salen);

// TODO: may not use it
void Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr);

// TODO: may not use it
void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr);

// flags defaults: 0
ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags);

// udp may use this
ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		 struct sockaddr *sa, socklen_t *salenptr);

ssize_t Recvmsg(int fd, struct msghdr *msg, int flags);

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout);

void Send(int fd, const void *ptr, size_t nbytes, int flags);

void Sendto(int fd, const void *ptr, size_t nbytes, int flags, 
            const struct sockaddr *sa, socklen_t salen);

void Sendmsg(int fd, const struct msghdr *msg, int flags);

void Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr);

void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);

void Shutdown(int fd, int how);

int Sockatmark(int fd);

void Socketpair(int family, int type, int protocol, int *fd);


} // namespace sys
} // namespace xnet



#endif // !_XNET_NET_SYSSOCKET_H_