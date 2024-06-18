# `pool_allocator::deallocate`

## Description

Deallocates a memory block of the specified size.

## Syntax

```cpp
void deallocate(pointer _Ptr, const size_type _Count) noexcept override;
```

## Parameters

- `_Ptr`: A pointer to the memory block to deallocate.
- `_Count`: The size of the memory block in bytes.

## Return value

(none)

## Exceptions

(none)

## Remarks

When called, the allocator first checks if the memory block comes from the associated resource. If so, it either creates a new list node to 
represent the deallocated block or merges it with an adjacent block if contiguous. Otherwise, there is no visible result.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [pool_allocator](pool_allocator.md)