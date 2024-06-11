# `operator==` (`object_allocator`)

## Description

Compares two allocators for equality.

## Syntax

```cpp
template <class _Ty>
bool operator==(const object_allocator<_Ty>& _Left, const object_allocator<_Ty>& _Right) noexcept;
```

## Parameters

- `_Left`: The left-side allocator to compare.
- `_Right`: The right-side allocator to compare.

## Return value

Returns true if the two allocators are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

Since the allocator is stateless, the result of this call is always true.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)