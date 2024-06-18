# `pool_resource::operator=`

## Description

Assigns a resource.

## Syntax

```cpp
pool_resource& operator=(const pool_resource& _Other);
pool_resource& operator=(pool_resource&& _Other) noexcept;
```

## Parameters

- `_Other`: The resource to assign from.

## Return value

Returns a reference to the resource that `_Other` was assigned to.

## Exceptions

* Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.
* (none)

## Remarks

The copying process does not copy the original memory block but rather allocates a new memory block of the same size, then copies 
the contents stored in the original block. The moving process transfers ownership of the memory block from `_Other`. Both versions call 
[destroy](pool_resource-destroy.md) before copying/moving.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<pool_resource.hpp>` |
| Minimum library version | `1.0.0`               |
| Maximum library version | `N/A`                 |

## See also

- [pool_resource](pool_resource.md)