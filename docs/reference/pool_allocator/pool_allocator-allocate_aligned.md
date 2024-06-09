# `pool_allocator::allocate_aligned`

## Description

Allocates a requested number of bytes aligned to the specified alignment from the associated resource.

## Syntax

```cpp
pointer allocate_aligned(const size_type _Count, const size_type _Align) override;
```

## Parameters

- `_Count`: The number of bytes to allocate.
- `_Align`: The requested alignment.

## Return value

Returns a pointer to the allocated memory block if successful; otherwise, returns a null pointer.

## Exceptions

- **Until version 1.0.0**: Throws [pool_exhausted](../exception/pool_exhausted.md) if the allocation fails.
- **Starting with version 1.0.1**: Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.

## Remarks

The function behaves similarly to [allocate](pool_allocator-allocate.md), except that it ensures the allocated memory is aligned to the 
specified alignment. It aligns the requested number of bytes to the specified alignment before attempting to allocate a block from the 
associated resource. The alignment process may result in allocating slightly more memory than requested to meet the alignment 
requirements. Note that the alignment must be a power of two.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [pool_allocator](pool_allocator.md)