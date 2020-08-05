/*
 * @Description: 
 * @Version: 1.0
 * @Autor: wx
 * @Date: 2020-07-28 10:43:48
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-08-04 22:08:41
 */ 
#ifndef _XNET_INETADDRESS_H_
#define _XNET_INETADDRESS_H_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <memory>
#include <string.h>

#include "../base/copyable.h"

namespace xnet
{
// sockaddr_in 的包裹类
class InetAddress : public copyable
{
public:
    InetAddress()
    {
        m_socklen = sizeof(m_sa);
        memset(&m_sa, 0x00, m_socklen);
    }
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
    socklen_t& len();

    struct sockaddr* sockaddr();
private:
    struct sockaddr_in m_sa;
    socklen_t m_socklen;
};

typedef std::shared_ptr<InetAddress*> InetAddressPtr;

} // namespace xnet


#endif // !_XNET_INETADDRESS_H_