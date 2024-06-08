# `dynamic_allocator`

## Description

Defines a stateless allocator that relies on memory management provided by the operating system.

## Syntax

```cpp
class dynamic_allocator {
public:
    using value_type      = allocator::value_type;
    using size_type       = allocator::size_type;
    using difference_type = allocator::difference_type;
    using pointer         = allocator::pointer;

    dynamic_allocator() noexcept;
    dynamic_allocator(const dynamic_allocator& _Other) noexcept;
    dynamic_allocator(dynamic_allocator&& _Other) noexcept;
    ~dynamic_allocator() noexcept override;

    dynamic_allocator& operator=(const dynamic_allocator& _Other) noexcept;
    dynamic_allocator& operator=(dynamic_allocator&& _Other) noexcept;

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

- [(constructor)](dynamic_allocator-ctor.md)
- [(destructor)](dynamic_allocator-dtor.md)
- [operator=](dynamic_allocator-operator-assign.md)
- [allocate](dynamic_allocator-allocate.md)
- [allocate_aligned](dynamic_allocator-allocate_aligned.md)
- [deallocate](dynamic_allocator-deallocate.md)
- [max_size](dynamic_allocator-max_size.md)
- [is_equal](dynamic_allocator-is_equal.md)

## Remarks

The allocator is stateless, which means it has no associated state like an underlying resource. It uses allocation and deallocation
algorithms provided by the operating system.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [allocator](../allocator/allocator.md)
- [block_allocator](../block_allocator/block_allocator.md)
- [object_allocator](../object_allocator/object_allocator.md)
- [pool_allocator](../pool_allocator/pool_allocator.md)
- [synchronized_allocator](../synchronized_allocator/synchronized_allocator.md)