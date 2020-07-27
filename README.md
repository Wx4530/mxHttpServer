# myWebServer

webServer by c++

- 使用epoll实现高并发
- 使用线程池来实现资源的合理利用

## 资源目录简介

- socket文件夹

>1. 利用系统api开发的网络通信组件
>2. 后续对其做一些封装

- webrc文件夹

>1. web资源根目录
>2. 存放网站资源

## 总体架构

- Reactor + Thread poll 实现基本网络库
- 利用自己的网络库实现一个http服务器
- http服务器现阶段只处理get和post请求
- post请求调用数据库访问函数来连接数据库
