# `block_allocator::(constructor)`

## Description

Creates a new `block_allocator` object.

## Syntax

```cpp
block_allocator(pool_resource& _Resource, const size_type _Block_size);
```

## Parameters

- `_Resource`: A reference to the resource to associate with.
- `_Block_size`: The requested block size.

## Return value

(none)

## Exceptions

Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.

## Remarks

Since the allocator is stateful, it must be initialized. During initialization, a bitmap is created to store information about each block. The 
size of the bitmap is calculated at runtime and is dynamically allocated, which is the only potentially risky situation during the allocator 
initialization.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `1.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)