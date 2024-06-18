# `block_allocator::allocate`

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

The function ensures that enough blocks are allocated to accommodate at least `_Count` bytes. If the requested number of bytes is not 
aligned to the block size, the allocator will allocate more memory than requested. For example, if `_Count` is not a multiple of the block 
size, additional blocks may be allocated to fulfill the request.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `1.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)