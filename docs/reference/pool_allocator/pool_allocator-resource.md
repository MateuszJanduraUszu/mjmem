# `pool_allocator::resource`

## Description

Retrieves the associated resource.

## Syntax

```cpp
const pool_resource& resource() const noexcept;
```

## Parameters

(none)

## Return value

Returns a read-only reference to the associated resource.

## Exceptions

(none)

## Remarks

The function retrieves the associated [resource](../pool_resource/pool_resource.md), which is a preallocated memory block managed by the allocator for quick variable-size allocations.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `2.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [pool_allocator](pool_allocator.md)