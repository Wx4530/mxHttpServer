#ifndef _XNET_BASE_NONCOPYABLE_H_
#define _XNET_BASE_NONCOPYABLE_H_

namespace xnet
{

class noncopyable
{
public:
// 设置拷贝构造和拷贝赋值为 delete
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};
   
}   // namespace xnet
#endif // !_XNET_BASE_NONCOPYABLE_H_



