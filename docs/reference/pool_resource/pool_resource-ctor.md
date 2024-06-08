# `pool_resource::(constructor)`

## Description

Creates a `pool_resource` object.

## Syntax

```cpp
pool_resource() noexcept;
pool_resource(const pool_resource& _Other);
pool_resource(pool_resource&& _Other) noexcept;
explicit pool_resource(const size_type _Size);
```

## Parameters

- `_Other`: A resource to copy or move from.
- `_Size`: Requested size of the new resource.

## Return value

(none)

## Exceptions

- (none)
- Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.
- (none)
- Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.

## Remarks

- The default constructor creates an empty resource, which is unusable.
- The copy constructor clones copies resource, allocating a new memory block of the same size and copying the contents.
- The move constructor transfers ownership of the memory block from the other resource to the new resource
- The sized constructor creates a new resource with the specified size

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<pool_resource.hpp>` |
| Minimum library version | `1.0.0`               |
| Maximum library version | `N/A`                 |

## See also

- [pool_resource](pool_resource.md)