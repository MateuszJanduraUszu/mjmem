# `block_allocator::deallocate`

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

When called, the allocator first checks if the memory block comes from the associated resource. If so, it resets a range of bits that 
represent the memory block. Otherwise, there is no visible result.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `1.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)