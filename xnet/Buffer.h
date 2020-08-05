/*
 * @Description: Buffer类, 接管数据的收发, 隔离sockfd的读取和写入操作
 * @Version: 1.0
 * @Autor: wx
 * @Date: 2020-07-24 12:28:39
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-07-30 23:28:43
 */ 
#ifndef _XNET_BUFFER_H_
#define _XNET_BUFFER_H_


#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <memory>
#include <algorithm>
#include <assert.h>

#include "../base/copyable.h"

namespace xnet
{

// 目前buffer类缓存的数据存放在栈区
/*
class : Buffer
用于提供一块内存来作为tcp nonblock 通信套接字的缓冲区
发送和接收数据时， 均先经过缓冲区buffer
*/
class Buffer : public xnet::copyable
{
public:
    // 默认缓冲区大小， 
    static const size_t kPreHeaderLen = 8;
    static const size_t kInitialSize = 1024;

    // Buffer();
    Buffer(size_t initialSize = 1024);

    // 返回可读的字节数， m_writeIndex - m_readIndex;
    size_t readableBytes()
    {
        return m_writeIndex - m_readIndex;
    }
    // 返回可写的字节数， m_writeIndex - m_readIndex;
    size_t writableBytes()
    {
        return capacity() - m_writeIndex;
    }
    // 返回vector左侧可写入区间的长度
    int leftBlank()
    {
        return m_readIndex - kPreHeaderLen;
    }
    // 返回读写位置的指针
    char* readPos()
    {
        return begin() + m_readIndex;
    }
    char* writePos()
    {
        return begin() + m_writeIndex;
    }

    const char* peek();
    void swap(Buffer&);
    void write(const void*, size_t);
    // 从文件描述符fd读取
    int readf(int fd);
    // 写入文件描述符
    int writef(int fd);
    // 从缓冲区读取
    int read(size_t n);
    // 向缓冲区追加数据
    void append(const char* data, size_t len);
    void append(const void* data, size_t len);

    // 更新读写下标
    void updateIdx(size_t len);
private:
    // 返回缓冲区头部字符
    char* begin()
    {
        return &*m_buf.begin();
    }
    const char* begin() const
    {
        return &*m_buf.begin();
    }
    size_t capacity()
    {
        return m_buf.capacity();
    }
    // 写入空间不足时调用,传入需要的空间大小
    void makeSpace(size_t addlen);
    // 将buffer中的数据左对齐到初始位置
    void move2left();

private:
    // 类数据成员
    std::vector<char> m_buf;
    // m_buf: 0 <= readIndex <= m_writeIndex < m_buf.capacity();
    // 两个下标把缓冲区分成三块， leftBlank, readableBytes, writableBytes;
    size_t m_readIndex;
    size_t m_writeIndex;
};

} // namespace xnet


#endif // !_XNET_BUFFER_H_