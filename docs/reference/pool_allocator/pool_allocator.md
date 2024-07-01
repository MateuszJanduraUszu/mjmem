# `pool_allocator`

## Description

Defines a variable-size block allocator associated with a [resource](../pool_resource/pool_resource.md).

## Syntax

```cpp
class pool_allocator {
public:
    using value_type      = allocator::value_type;
    using size_type       = allocator::size_type;
    using difference_type = allocator::difference_type;
    using pointer         = allocator::pointer;

    static constexpr size_type unbounded_block_size = static_cast<size_type>(-1);

    pool_allocator(pool_resource& _Resource, const size_type _Max_block_size = unbounded_block_size);
    ~pool_allocator() noexcept override;
    
    pool_allocator()                                 = delete;
    pool_allocator(const pool_allocator&)            = delete;
    pool_allocator& operator=(const pool_allocator&) = delete;

    pointer allocate(const size_type _Count) override;
    pointer allocate_aligned(const size_type _Count, const size_type _Align) override;
    void deallocate(pointer _Ptr, const size_type _Count) noexcept override;
    size_type max_size() const noexcept override;
    bool is_equal(const allocator& _Other) const noexcept override;
    const pool_resource& resource() const noexcept;
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

- [(constructor)](pool_allocator-ctor.md)
- [(destructor)](pool_allocator-dtor.md)
- [allocate](pool_allocator-allocate.md)
- [allocate_aligned](pool_allocator-allocate_aligned.md)
- [deallocate](pool_allocator-deallocate.md)
- [max_size](pool_allocator-max_size.md)
- [is_equal](pool_allocator-is_equal.md)
- [free_blocks](pool_allocator-free_blocks.md)
- [resource](pool_allocator-resource.md)

## Member constants

| Constant             | Definition                    | Value                      |
|----------------------|-------------------------------|----------------------------|
| unbounded_block_size | Indicates no allocation limit | static_cast<size_type>(-1) |

## Non-member functions

(none)

## Remarks

The allocator operates on a user-provided preallocated memory block stored in the associated resource. It employs a sorted 
doubly-linked list of free blocks to store information about available blocks.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [allocator](../allocator/allocator.md)
- [block_allocator](../block_allocator/block_allocator.md)
- [dynamic_allocator](../dynamic_allocator/dynamic_allocator.md)
- [object_allocator](../object_allocator/object_allocator.md)
- [synchronized_allocator](../synchronized_allocator/synchronized_allocator.md)