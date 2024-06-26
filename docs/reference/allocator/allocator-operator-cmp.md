# `operator==` (`allocator`)

## Description

Compares two allocators for equality.

## Syntax

```cpp
bool operator==(const allocator& _Left, const allocator& _Right) noexcept;
```

## Parameters

- `_Left`: The left-side allocator to compare.
- `_Right`: The right-side allocator to compare.

## Return value

Returns true if the two allocators are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function effectively calls `_Left.is_equal(_Right)` to compare two allocators. It is likely that `is_equal` is overridden by a derived class.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<allocator.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocator](allocator.md)