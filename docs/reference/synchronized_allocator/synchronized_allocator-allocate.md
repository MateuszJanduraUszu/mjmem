# `synchronized_allocator::allocate`

## Description

Allocates a requested number of bytes using the associated allocator.

## Syntax

```cpp
pointer allocate(const size_type _Count) override;
```

## Parameters

- `_Count`: The number of bytes to allocate.

## Return value

Returns a pointer to the allocated memory block if successful; otherwise, returns a null pointer.

## Exceptions

May throw the associated allocator's specific exception if the allocation fails.

## Remarks

The function internally calls the associated allocator's `allocate` function in a locked context, ensuring thread-safe access.

## Requirements

| Requirement             | Value                          |
|-------------------------|--------------------------------|
| Include header          | `<synchronized_allocator.hpp>` |
| Minimum library version | `1.0.0`                        |
| Maximum library version | `N/A`                          |

## See also

- [synchronized_allocator](synchronized_allocator.md)