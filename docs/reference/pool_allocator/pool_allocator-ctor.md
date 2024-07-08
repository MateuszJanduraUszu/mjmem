# `pool_allocator::(constructor)`

## Description

Creates a new `pool_allocator` object.

## Syntax

```cpp
pool_allocator(pool_resource& _Resource, const size_type _Max_block_size);
```

## Parameters

- `_Resource`: A reference to the resource to associate with.
- `_Max_block_size`: The maximum number of bytes per allocation. Defaults to `unbounded_block_size`, which indicates no allocation limit.

## Return value

(none)

## Exceptions

Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.

## Remarks

Since the allocator is stateful, it must be initialized first. During initialization, a sorted singly-linked list of free blocks is created. Initially, 
the list contains only one free block, which represents the entire memory block from the associated resource.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [pool_allocator](pool_allocator.md)