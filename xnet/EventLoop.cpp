/*
 * @Description: 
 * @Version: 1.0
 * @Autor: wx
 * @Date: 2020-07-28 10:43:48
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-07-29 22:52:02
 */ 
#include <strings.h>

#include "../xnet/EventLoop.h"
#include "../xnet/sysAPI/SysSocket.h"

using namespace xnet;

namespace cb
{
 
void handle_connect(int lfd, int epfd)
{
    InetAddress caddr;
    Socket cSocket;
    cSocket.fd = sys::Accept(lfd, caddr.sockaddr(), &caddr.len()); 
    if (cSocket.fd == -1)
    {
        perror("accept error");
        exit(1);
    }

    // 成功建立连接，输出连接信息
    printf("------New Client connected! fd:%d %s\n------",
        cSocket.fd, caddr.getIpPort_p());

    // cfd加入epoll树
    struct epoll_event t_epev;
    // 初始化sfdevt信息
    t_epev.events = EPOLLIN | EPOLLET;
    t_epev.data.fd = cSocket.fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, cSocket.fd, &t_epev);
}

void handle_data(int cfd, int epfd)
{
    // 建立通信
	int len = -1;
	do{
		char buf[8192] = {0};
		if ( (len = sys::Recv(cfd, buf, sizeof(buf), 0)) == 0 || errno == 104)
            break;
        printf("Recv(fd = %d): %s len = %d\n", cfd, buf, len);
        // 把数据发给客户端
        sys::Send(cfd, buf, strlen(buf) + 1, 0);
	}while(len);
}

   
} // namespace cb

void EventLoop::initAllCallBack()
{
    onConnectCallBack = cb::handle_connect;
    onMessageCallBack = cb::handle_data;
}

EventLoop::EventLoop(int lfd)
    :   m_lsocket(lfd),
        m_pool()
{ }

EventLoop::EventLoop(int lfd, int nthrs)
    :   m_lsocket(lfd),
        m_pool(nthrs)
{ }

void EventLoop::init()
{
    // 创建epoll树 设置监听事件集
    m_epfd = epoll_create1(EPOLL_CLOEXEC);
    m_events = new event[MAX_EVENTS];
    initAllCallBack();
}

EventLoop::~EventLoop()
{
    delete[] m_events;
}

void EventLoop::loop()
{
    for( ; ; )
    {
        // 这里检查不活跃连接, 或者用定时器来管理
        int t_eventCnt = epoll_wait(m_epfd, m_events, MAX_EVENTS, -1);
        for(int i = 0; i < t_eventCnt; ++i)
        {
            int fd = m_events[i].data.fd;
            if( fd == m_lsocket.fd )
            {
                m_pool.enqueue(std::bind(onConnectCallBack, fd, m_epfd));
            }
            else
            {
                m_pool.enqueue(std::bind(onMessageCallBack, fd, m_epfd));
            }
        }
    }
}

// void EventLoop::addClient(int fd)
// {
//     event ev;
//     bzero(&ev, sizeof(ev));
//     ev.data.fd = fd;
//     ev.events = EPOLLIN | EPOLLET;
//     epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &ev);
// }