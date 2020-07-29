#ifndef _XNET_WRAPSOCK_H_
#define _XNET_WRAPSOCK_H_

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "InetAddress.h"
#include "../base/Buffer.h"
#include "./sysAPI/SysSocket.h"

namespace xnet
{

// 自带缓冲区的socket套接字
class Socket
{
public:
    Socket()
        :   m_bufin(),
            m_bufout()
    {
        this->fd = sys::Socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC | SOCK_NONBLOCK, IPPROTO_TCP);
    }
    explicit Socket(int sockfd)
        :   fd(sockfd),
            m_bufin(),
            m_bufout()
    { }
    
    ~Socket()
    {
        close(this->fd);
    }

    void setFlags(int newflags)
    {
        fcntl(fd, F_SETFL, newflags);
    }

public:
    int fd;
    Buffer m_bufin;
    Buffer m_bufout;
};  

typedef std::shared_ptr<Socket> SocketPtr;

} // namespace xnet

#endif // !_XNET_WRAPSOCK_H_