# `pool_resource`

## Description

Manages a contiguous memory block which serves as a resource for stateful allocators.

## Syntax

```cpp
class pool_resource {
public:
    using value_type      = allocator::value_type;
    using size_type       = allocator::size_type;
    using difference_type = allocator::difference_type;
    using pointer         = allocator::pointer;
    using const_pointer   = const pointer;

    pool_resource() noexcept;
    pool_resource(const pool_resource& _Other);
    pool_resource(pool_resource&& _Other) noexcept;
    ~pool_resource() noexcept;

    explicit pool_resource(const size_type _Size);

    pool_resource& operator=(const pool_resource& _Other);
    pool_resource& operator=(pool_resource&& _Other) noexcept;

    bool empty() const noexcept;
    pointer data() noexcept;
    const_pointer data() const noexcept;
    size_type size() const noexcept;
    bool contains(const_pointer _Block, const size_type _Size) const noexcept;
    void swap(pool_resource& _Other) noexcept;
    pointer release() noexcept;
    void destroy() noexcept;
};
```

## Member types

| Type            | Definition                 |
|-----------------|----------------------------|
| value_type      | allocator::value_type      |
| size_type       | allocator::size_type       |
| difference_type | allocator::difference_type |
| pointer         | allocator::pointer         |
| const_pointer   | const pointer              |

## Member functions

- [(constructor)](pool_resource-ctor.md)
- [(destructor)](pool_resource-dtor.md)
- [operator=](pool_resource-operator-assign.md)
- [empty](pool_resource-empty.md)
- [data](pool_resource-data.md)
- [size](pool_resource-size.md)
- [contains](pool_resource-contains.md)
- [swap](pool_resource-swap.md)
- [release](pool_resource-release.md)
- [destroy](pool_resource-destroy.md)

## Non-member functions

- [operator==](pool_resource-operator-cmp.md)

## Remarks

The `pool_resource` class is used by stateful allocators to provide a working resource. It is important to note that the copying process
does not exactly replicate the memory block; instead, it allocates a new block of the same size and copies the stored data. This
behavior ensures that the original and copied objects are independent.

## Requirements

| Requirement     | Value                 |
|-----------------|-----------------------|
| Include header  | `<pool_resource.hpp>` |
| Library version | `1.0.0` or newer      |

## See also

- [block_allocator](../block_allocator/block_allocator.md)
- [pool_allocator](../pool_allocator/pool_allocator.md)