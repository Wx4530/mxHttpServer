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
        m_sockfd = sys::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    explicit Socket(int sockfd)
        :   m_sockfd(sockfd),
            m_bufin(),
            m_bufout()
    { }
    
    ~Socket()
    {
        close(m_sockfd);
    }

    void setFlags(int flags);

    int fd()
    {
        return m_sockfd;
    }

private:
    int m_sockfd;
    Buffer m_bufin;
    Buffer m_bufout;
};  

typedef std::shared_ptr<Socket> SocketPtr;

} // namespace xnet

#endif // !_XNET_WRAPSOCK_H_