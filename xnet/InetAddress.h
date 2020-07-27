#ifndef _XNET_INETADDRESS_H_
#define _XNET_INETADDRESS_H_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <memory>

#include "../base/copyable.h"

namespace xnet
{
namespace net
{

// sockaddr_in 的包裹类
class InetAddress : public copyable
{
public:
    InetAddress(int port);
    InetAddress(const std::string& addr, const int port);
    InetAddress(const std::string& ip_port);
    InetAddress(const struct sockaddr_in& addr);
    InetAddress(const struct sockaddr_in&& addr);
    //初始化sockaddr_in
    void init();
    std::string getIpPort_p();
    in_addr_t getIp_n();
    std::string getIp_p();
    in_port_t getPort_n();
    uint16_t getPort_p();
    socklen_t getlen();

    const struct sockaddr* sockaddr();
private:
    struct sockaddr_in m_sa;
    socklen_t m_socklen;
};

typedef std::shared_ptr<InetAddress*> InetAddressPtr;

} // namespace net
} // namespace xnet


#endif // !_XNET_INETADDRESS_H_