/*
 * @description: 
 * @author: wx
 * @github: https://github.com/Wx4530/myWebServer.git
 * @lastEditors: wx
 * @Date: 2020-07-23 00:09:34
 * @LastEditTime: 2020-07-25 21:40:15
 * @Copyright: 1.0
 */ 

#include <vector>
#include <functional>

#include "../base/noncopyable.h"
#include "../mxnet/SysSocket.h"
#include "../mxnet/InetAddress.h"
#include "sys/epoll.h"

namespace xnet
{
namespace net
{

class InetAddress;
using callback = std::function<void()>;
using event = struct epoll_event;
// TODO: 最大监听事件数以后可能会改
static const int MAX_EVENTS = 1024;

class EventLoop : noncopyable
{
public:
    EventLoop(int lfd, const InetAddress& addr);
    ~EventLoop();
private:
    int m_epfd;
    event* events;

};



} // namespace net

    
} // namespace xnet
