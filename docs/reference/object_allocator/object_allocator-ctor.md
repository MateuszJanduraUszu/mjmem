# `object_allocator::(constructor)`

## Description

Creates a new `object_allocator` object.

## Syntax

```cpp
object_allocator() noexcept                        = default;
object_allocator(const object_allocator&) noexcept = default;
object_allocator(object_allocator&&) noexcept      = default;

template <class _Other>
object_allocator(const object_allocator<_Other>& _Al) noexcept;
```

## Parameters

- `_Al`: The allocator to construct with.

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the allocator is stateless, the construction is trivial; therefore, the constructors do not perform specific actions.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)