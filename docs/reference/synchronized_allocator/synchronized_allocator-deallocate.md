# `synchronized_allocator::deallocate`

## Description

Deallocates a memory block of the specified size.

## Syntax

```cpp
void deallocate(pointer _Ptr, const size_type _Count) noexcept override;
```

## Parameters

- `_Ptr`: A pointer to the memory block to deallocate.
- `_Count`: The size of the memory block in bytes.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function internally calls the associated allocator's `deallocate` function in a locked context, ensuring thread-safe access.

## Requirements

| Requirement             | Value                          |
|-------------------------|--------------------------------|
| Include header          | `<synchronized_allocator.hpp>` |
| Minimum library version | `1.0.0`                        |
| Maximum library version | `N/A`                          |

## See also

- [synchronized_allocator](synchronized_allocator.md)