# `synchronized_allocator::is_equal`

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

The function internally calls the associated allocator's `is_equal` function in a locked context, ensuring thread-safe access. Note that 
`_Other` must be castable from [allocator](../allocator/allocator.md) to `synchronized_allocator`; otherwise, it always returns false.

## Requirements

| Requirement             | Value                          |
|-------------------------|--------------------------------|
| Include header          | `<synchronized_allocator.hpp>` |
| Minimum library version | `1.0.0`                        |
| Maximum library version | `N/A`                          |

## See also

- [synchronized_allocator](synchronized_allocator.md)