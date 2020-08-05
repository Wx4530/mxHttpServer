
#include <memory>

#include "Buffer.h"

using namespace std;
using namespace xnet;

// Buffer::Buffer()
//     :   m_readIndex(kPreHeaderLen),
//         m_writeIndex(kPreHeaderLen)
// {
//     assert(readableBytes() == 0);
//     assert(writableBytes() == kInitialSize);
//     assert(leftBlank() == kPreHeaderLen);
//     m_buf.reserve(kPreHeaderLen + kInitialSize);
// }

Buffer::Buffer(size_t initialSize)
    :   m_readIndex(kPreHeaderLen),
        m_writeIndex(kPreHeaderLen)
{
    m_buf.reserve(kPreHeaderLen + initialSize);
    assert(readableBytes() == 0);
    assert(writableBytes() == initialSize);
    assert(leftBlank() == 0);
}

// 找到开始读取的地址
const char* Buffer::peek()
{
    return begin() + m_readIndex;
}

void Buffer::append(const char* data, size_t len)
{
    
}

void Buffer::append(const void* data, size_t len)
{
    append(static_cast<const char*>(data), len);
}

void Buffer::write(const void* data, size_t len)
{
    string str(static_cast<char*>( const_cast<void*>(data) ));
    // 空间不够则填入
    if(len > writableBytes())
    {
        len *= sizeof(data);
        makeSpace(len);
    }
    // 添加数据
    std::copy(str.begin(), str.end(), begin() + m_writeIndex);
}


// 交换两个Buffer对象
void Buffer::swap(Buffer&)
{

}

// 从文件描述符fd读取
int Buffer::readf(int fd)
{

}

int Buffer::writef(int fd)
{

}

// 从缓冲区读取
int Buffer::read(size_t n)
{

}

void Buffer::makeSpace(size_t addlen)
{
    if(leftBlank() + writableBytes() < addlen)
    {
        m_buf.resize(m_writeIndex + addlen);
    }
    else
    {
        move2left();
    }
}
// 将buffer中的数据左对齐到初始位置
void Buffer::move2left()
{
    std::copy(begin() + m_readIndex, begin() + m_writeIndex, begin() + kPreHeaderLen);
    m_writeIndex = m_writeIndex - m_readIndex + kPreHeaderLen;
    m_readIndex = kPreHeaderLen;
}