# `synchronized_allocator`

## Description

Defines an allocator that manages access to the associated allocator in a multithreading environment.

## Syntax

```cpp
class synchronized_allocator {
public:
    using value_type      = allocator::value_type;
    using size_type       = allocator::size_type;
    using difference_type = allocator::difference_type;
    using pointer         = allocator::pointer;

    explicit synchronized_allocator(allocator& _Al) noexcept;
    ~synchronized_allocator() noexcept override;

    synchronized_allocator()                                         = delete;
    synchronized_allocator(const synchronized_allocator&)            = delete;
    synchronized_allocator& operator=(const synchronized_allocator&) = delete;

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

- [(constructor)](synchronized_allocator-ctor.md)
- [(destructor)](synchronized_allocator-dtor.md)
- [allocate](synchronized_allocator-allocate.md)
- [allocate_aligned](synchronized_allocator-allocate_aligned.md)
- [deallocate](synchronized_allocator-deallocate.md)
- [max_size](synchronized_allocator-max_size.md)
- [is_equal](synchronized_allocator-is_equal.md)

## Remarks

The allocator uses a Slim Read/Write Lock (SRW Lock) to manage access to the associated allocator. It can acquire either read-only or 
read-write access, depending on the accessing function's requirements. This ensures thread-safe operations for memory allocation 
and deallocation.

## Requirements

| Requirement             | Value                          |
|-------------------------|--------------------------------|
| Include header          | `<synchronized_allocator.hpp>` |
| Minimum library version | `1.0.0`                        |
| Maximum library version | `N/A`                          |

## See also

- [allocator](../allocator/allocator.md)
- [block_allocator](../block_allocator/block_allocator.md)
- [dynamic_allocator](../dynamic_allocator/dynamic_allocator.md)
- [object_allocator](../object_allocator/object_allocator.md)
- [pool_allocator](../pool_allocator/pool_allocator.md)