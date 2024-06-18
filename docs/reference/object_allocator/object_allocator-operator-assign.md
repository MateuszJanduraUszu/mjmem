# `object_allocator::operator=`

## Description

Assigns an allocator.

## Syntax

```cpp
object_allocator& operator=(const object_allocator&) noexcept = default;
object_allocator& operator=(object_allocator&&) noexcept      = default;

template <class _Other>
object_allocator& operator=(const object_allocator<_Other>& _Al) noexcept;
```

## Parameters

- `_Al`: The allocator to assign from.

## Return value

Returns a reference to the allocator that `_Al` was assigned to.

## Exceptions

(none)

## Remarks

Since the allocator is stateless, it does not perform any assignments. Therefore, the assign operator is trivial.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)