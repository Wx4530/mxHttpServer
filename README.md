# myHttpServer

HttpServer by c++

- 使用epoll实现高并发
- 使用线程池来实现资源的合理利用

## 资源目录简介


- webrc文件夹

>1. web资源根目录
>2. 存放网站资源

## 总体架构

- Reactor + Thread poll 实现基本网络库
  - 服务器共用一个Reactor， 一个线程池， 线程池大小，可以通过后续的cpu资源占用情况来调整，理想情况下， 最大负载（连接数）时应跑满CPU
  - 
- 利用自己的网络库实现一个http服务器
- http服务器现阶段只处理get和post请求
- post请求调用数据库访问函数来连接数据库


## 通用基础

- Buffer: 用于socket通信的缓冲区
- sync.h: 互斥锁条件变量和信号量
- Thread: 对pthread做的简单的封装,


## 网络通信基础

- InetAddress: IP:port的封装, 可以方便的对ip+port初始化并显示
- Socket: 带缓冲区的Socket类
- SysSocket: 一些系统API的包裹函数

## 并发支持

- ThreadPool:   线程池, 核心为工作线程组和任务队列
- EventLoop:    Reactor事件分发器, 核心为epoll, 默认是单线程

## HTTP支持

- request: 报头分析类, 负责解析http数据报, 支持GET和POST请求
- response: 生成回应类, 负责组装响应头
  
## 用以上组件搭建的TCP和HTTP服务器

- TcpServer: TCP echo服务器, 支持高并发
- HttpServer: http服务器, 支持GET和POST请求, 支持高并发, webbench测试下最高并发数可达到********

## 其他组件(TODO:)

- Logger: 日志类, 实现同步/异步写日志功能
- Timer: 定时器类, 实现一些定时功能(优先队列? )
  - 关于连接: 长时间不用的客户端, 关闭响应功能
  - 关于推送: 服务器实现一个简易的推送功能

## 类间依赖关系

