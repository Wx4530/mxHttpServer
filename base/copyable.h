#ifndef XNET_BASE_COPYABLE_H
#define XNET_BASE_COPYABLE_H

namespace xnet
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable
{
protected:
    copyable() = default;
    ~copyable() = default;
};

}  // namespace xnet

#endif  // XNET_BASE_COPYABLE_H
