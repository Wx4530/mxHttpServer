#ifndef _XNET_TCPSERVER_H_
#define _XNET_TCPSERVER_H_

#include <map>

#include "EventLoop.h"
#include "../base/noncopyable.h"

namespace xnet
{

class TcpServer : noncopyable
{
public:
    TcpServer(int port, int nthread);
    ~TcpServer();
    
private:
    EventLoop m_loop;
    int m_lfd;
    InetAddress m_saddr
    
    // 连接列表
    // std::map<Timer, Socket&> conns;
};



} // namespace xnet


#endif // !_XNET_TCPSERVER_H_