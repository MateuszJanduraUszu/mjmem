# `dynamic_allocator::is_equal`

## Description

Compares two allocators for equality.

## Syntax

```cpp
bool is_equal(const allocator& _Other) const noexcept override;
```

## Parameters

- `_Other`: The allocator to compare with.

## Return value

Returns true if the two allocators are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

Since the allocator is stateless, two `dynamic_allocator`s are always considered equal. Note that `_Other` must be castable from
[allocator](../allocator/allocator.md) to `dynamic_allocator`; otherwise, the return value is false.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)