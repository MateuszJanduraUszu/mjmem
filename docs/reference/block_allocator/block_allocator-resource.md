# `block_allocator::resource`

## Description

Retrieves the associated resource.

## Syntax

```cpp
const pool_resource& resource() const noexcept;
```

## Parameters

(none)

## Return value

Returns the associated resource.

## Exceptions

(none)

## Remarks

The function returns the associated [resource](../pool_resource/pool_resource.md), which is a preallocated memory block managed by 
the allocator for quick fixed-size allocations. 

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `2.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)