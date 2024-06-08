# `block_allocator::is_equal`

## Description

Compares two allocators for equality.

## Syntax

```cpp
bool is_equal(const allocator& _Other) const noexcept override;
```

## Parameters

- `_Other`: An allocator to compare with.

## Return value

Returns true if the two allocators are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

The two allocators are considered equal when they use the same resource. Note that `_Other` must be castable from 
[allocator](../allocator/allocator.md) to `block_allocator`; otherwise, it always returns false.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `1.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)