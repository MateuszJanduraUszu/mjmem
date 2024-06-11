# `dynamic_allocator::allocate_aligned`

## Description

Allocates a requested number of bytes aligned to the requested alignment.

## Syntax

```cpp
pointer allocate_aligned(const size_type _Count, cons size_type _Align) override;
```

## Parameters

- `_Count`: The number of bytes.
- `_Align`: The requested alignment.

## Return value

Returns a pointer to the allocated memory block if successful; otherwise, returns a null pointer.

## Exceptions

Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.

## Remarks

The behavior of this function is the same as [allocate](dynamic_allocator-allocate.md), except that the requested number of bytes is
aligned to the specified alignment. Note that alignment must be a power of two.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)