# `pool_allocator::free_blocks`

## Description

> **Important**: This function has been deprecated and removed from the library since version 2.0.0.

Retrieves the number of free blocks.

## Syntax

```cpp
size_type free_blocks() const noexcept;
```

## Parameters

(none)

## Return value

Returns the number of free blocks.

## Exceptions

(none)

## Remarks

The function returns the number of free blocks currently available in the allocator. It is equivalent to retrieving the size of the internal list 
of free blocks.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `1.0.2`                |

## See also

- [pool_allocator](pool_allocator.md)