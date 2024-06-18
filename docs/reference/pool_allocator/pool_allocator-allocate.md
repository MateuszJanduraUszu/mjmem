# `pool_allocator::allocate`

## Description

Allocates a requested number of bytes from the associated resource.

## Syntax

```cpp
pointer allocate(const size_type _Count) override;
```

## Parameters

- `_Count`: The number of bytes to allocate.

## Return value

Returns a pointer to the allocated memory block if successful; otherwise, returns a null pointer.

## Exceptions

- **Until version 1.0.0**: Throws [pool_exhausted](../exception/pool_exhausted.md) if the allocation fails.
- **Starting from version 1.0.1**: Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.

## Remarks

When the function is called, it searches the list of free blocks for one that is at least the requested number of bytes. Since the list is 
sorted, the smallest suitable block is selected. If the selected block is the same size as the requested number of bytes, the node is 
deleted from the list. Otherwise, the node's offset and size are updated to reflect the allocation.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [pool_allocator](pool_allocator.md)