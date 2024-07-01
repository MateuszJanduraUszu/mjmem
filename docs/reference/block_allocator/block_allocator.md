# `block_allocator`

## Description

Defines a stateful fixed-size block allocator associated with a [resource](../pool_resource/pool_resource.md).

## Syntax

```cpp
class block_allocator {
public:
    using value_type      = allocator::value_type;
    using size_type       = allocator::size_type;
    using difference_type = allocator::difference_type;
    using pointer         = allocator::pointer;

    block_allocator(pool_resource& _Resource, const size_type _Block_size);
    ~block_allocator() noexcept override;

    block_allocator()                                  = delete;
    block_allocator(const block_allocator&)            = delete;
    block_allocator& operator=(const block_allocator&) = delete;

    pointer allocate(const size_type _Count) override;
    pointer allocate_aligned(const size_type _Count, const size_type _Align) override;
    void deallocate(pointer _Ptr, const size_type _Count) noexcept override;
    size_type max_size() const noexcept override;
    bool is_equal(const allocator& _Other) const noexcept override;
};
```

## Member types

| Type            | Definition                 |
|-----------------|----------------------------|
| value_type      | allocator::value_type      |
| size_type       | allocator::size_type       |
| difference_type | allocator::difference_type |
| pointer         | allocator::pointer         |

## Member functions

- [(constructor)](block_allocator-ctor.md)
- [(destructor)](block_allocator-dtor.md)
- [allocate](block_allocator-allocate.md)
- [allocate_aligned](block_allocator-allocate_aligned.md)
- [deallocate](block_allocator-deallocate.md)
- [max_size](block_allocator-max_size.md)
- [is_equal](block_allocator-is_equal.md)
- [block_size](block_allocator-block_size.md)
- [resource](block_allocator-resource.md)

## Member constants

(none)

## Non-member functions

(none)

## Remarks

The allocator operates on user-specified fixed-size blocks. This type of allocator is especially useful when working on the same 
fixed-size objects which are frequently allocated and deallocated. To store information about block status, a bitmap is used, where 
each bit represents a single block. This allows for efficient tracking of block availability.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `1.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [allocator](../allocator/allocator.md)
- [dynamic_allocator](../dynamic_allocator/dynamic_allocator.md)
- [object_allocator](../object_allocator/object_allocator.md)
- [pool_allocator](../pool_allocator/pool_allocator.md)
- [synchronized_allocator](../synchronized_allocator/synchronized_allocator.md)