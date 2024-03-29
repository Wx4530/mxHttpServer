/*
 * @description: 
 * @author: wx
 * @github: https://github.com/Wx4530/myWebServer.git
 * @lastEditors: wx
 * @Date: 2020-07-23 00:09:34
 * @LastEditTime: 2020-08-05 11:58:16
 * @Copyright: 1.0
 */ 
#ifndef _XNET_EVENTLOOP_H_
#define _XNET_EVENTLOOP_H_

#include <sys/epoll.h>
#include <functional>
#include <memory>

#include "../base/noncopyable.h"
#include "../Threadpool/Threadpool.h"
#include "../xnet/Socket.h"
#include "../xnet/InetAddress.h"

namespace xnet
{

using callback = std::function<void(int, int)>;
using event = struct epoll_event;
// TODO: 最大监听事件数以后可能会改
static const int MAX_EVENTS = 1024;

class EventLoop : noncopyable
{
public:
    // 无参构造, 不预设监听套接字事件
    // EventLoop();
    // EventLoop(int lfd);
    // 有参构造, 设置监听套接字和线程池大小, 2 * kernel + 2
    EventLoop();
    ~EventLoop();

    // 初始化回调函数
    void initAllCallBack();
    // 初始化公共部分
    void init();
    // 设置回调函数
    void setCallBack(callback onConnect_cb, callback onMessage_cb);
    void addClient(int fd);
    void addServer(int fd);
    void loop(); 
private:
    int m_epfd;
    Socket m_lsocket;
    InetAddress m_saddr;
    event* m_events;
    callback onMessageCallBack;
    callback onConnectCallBack;
    ThreadPool m_pool;
};

    
} // namespace xnet

#endif // !_XNET_EVENTLOOP_H_