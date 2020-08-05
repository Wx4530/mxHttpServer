

#include "../xnet/InetAddress.h"

using namespace std;
using namespace xnet;

// 使用默认地址, 用户指定端口
InetAddress::InetAddress(int port)
{
    this->init();
    m_sa.sin_port = htons(port);
}

// addr格式应该为"1.2.3.4"
InetAddress::InetAddress(const std::string& addr, const int port)
{
    this->init();
    inet_pton(AF_INET, addr.c_str(), &m_sa.sin_addr.s_addr);
    m_sa.sin_port = htons(port);
}

// 转换"ip:port"格式的字符串为sockaddr
InetAddress::InetAddress(const std::string& ip_port)
{
    this->init();
    std::string s_ipport(ip_port.c_str());
    int pos = s_ipport.find(":");
    inet_pton(AF_INET, s_ipport.substr(0, pos).c_str(), &m_sa.sin_addr.s_addr);
    m_sa.sin_port = htons( atoi( s_ipport.substr(pos + 1).c_str() ) );
}

// copy构造
InetAddress::InetAddress(const struct sockaddr_in& addr)
{
    m_sa.sin_family = addr.sin_family;
    m_sa.sin_addr = addr.sin_addr;
    m_sa.sin_port = addr.sin_port;
}

// move构造函数
InetAddress::InetAddress(const struct sockaddr_in&& addr)
{
    m_sa = std::move(addr);
}

// 初始化基本成员
void InetAddress::init()
{
    memset(&m_sa, 0x00, sizeof(m_sa));
    m_sa.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sa.sin_family = AF_INET;
    m_socklen = sizeof(m_sa);
}

// 获取地址+端口的描述, 格式:8.8.8.8:0000
std::string InetAddress::getIpPort_p()
{
    char buf[22] = {0};
    char port[6] = {0};

    inet_ntop(AF_INET, &m_sa.sin_addr.s_addr, buf, 16);
    snprintf(port, 6, ":%u", ntohs(m_sa.sin_port));
    strncat(buf, port, strlen(port));

    return std::string(buf);
}

// 获取网络字节序(大端字节序)的ip
// TODO: 大端字节序:
in_addr_t InetAddress::getIp_n()
{
    return m_sa.sin_addr.s_addr;
}

// 获取ip字符串
std::string InetAddress::getIp_p()
{
    char buf[16] = {0};
    inet_ntop(AF_INET, &m_sa.sin_addr.s_addr, buf, 16);
    return std::string(buf);
}

// 获取网络字节序的端口
in_port_t InetAddress::getPort_n()
{
    return m_sa.sin_port;
}

// 获取端口的数值形式
uint16_t InetAddress::getPort_p()
{
    return ntohs(m_sa.sin_port);
}

// 获取sockaddr对象
struct sockaddr* InetAddress::sockaddr()
{
    return static_cast<struct sockaddr*>(static_cast<void*>(&m_sa));
}

// 获取socklen_t
socklen_t InetAddress::getlen()
{
    return m_socklen;
}

// 获取socklen_t
socklen_t& InetAddress::len()
{
    return m_socklen;
}