# `object_allocator`

## Description

Defines a stateless allocator that serves as a type-specific wrapper around the global allocator.

## Syntax

```cpp
template <class _Ty>
class object_allocator {
public:
    using value_type      = _Ty;
    using size_type       = allocator::size_type;
    using difference_type = allocator::difference_type;
    using pointer         = _Ty*;
    using const_pointer   = const _Ty*;
    using reference       = _Ty&;
    using const_reference = const _Ty&;

    template <class _Other>
    struct rebind {
        using other = object_allocator<_Other>;
    };

    object_allocator() noexcept                        = default;
    object_allocator(const object_allocator&) noexcept = default;
    object_allocator(object_allocator&&) noexcept      = default;
    ~object_allocator() noexcept                       = default;
    
    template <class _Other>
    object_allocator(const object_allocator<_Other>& _Other) noexcept;

    object_allocator& operator=(const object_allocator&) noexcept = default;
    object_allocator& operator=(object_allocator&&) noexcept      = default;

    template <class _Other>
    object_allocator& operator=(const object_allocator<_Other>& _Other) noexcept;

    pointer allocate(const size_type _Count);
    pointer allocate_aligned(const size_type _Count, const size_type _Align);
    void deallocate(pointer _Ptr, const size_type _Count) noexcept;
    size_type max_size() const noexcept;
    bool is_equal(const object_allocator&) const noexcept;
};
```

## Member types

| Type            | Definition                                                                                              |
|-----------------|---------------------------------------------------------------------------------------------------------|
| value_type      | _Ty                                                                                                     |
| size_type       | allocator::size_type                                                                                    |
| difference_type | allocator::difference_type                                                                              |
| pointer         | _Ty*                                                                                                    |
| const_pointer   | const _Ty*                                                                                              |
| reference       | _Ty&                                                                                                    |
| const_reference | const _Ty&                                                                                              |
| rebind          | template &lt;class _Other&gt;<br>struct rebind {<br>&emsp;using other = object_allocator<_Other>;<br>}; |

## Member functions

- [(constructor)](object_allocator-ctor.md)
- [(destructor)](object_allocator-dtor.md)
- [operator=](object_allocator-operator-assign.md)
- [allocate](object_allocator-allocate.md)
- [allocate_aligned](object_allocator-allocate_aligned.md)
- [deallocate](object_allocator-deallocate.md)
- [max_size](object_allocator-max_size.md)
- [is_equal](object_allocator-is_equal.md)

## Member constants

(none)

## Non-member functions

- [operator==](object_allocator-operator-cmp.md)

## Remarks

The allocator uses the global allocator for the requested tasks, except it adjusts the passed arguments to be appropriate for the 
selected type, for example, allocating a number of objects of this type instead of bytes.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [allocator](../allocator/allocator.md)
- [block_allocator](../block_allocator/block_allocator.md)
- [dynamic_allocator](../dynamic_allocator/dynamic_allocator.md)
- [pool_allocator](../pool_allocator/pool_allocator.md)
- [synchronized_allocator](../synchronized_allocator/synchronized_allocator.md)