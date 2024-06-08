# `dynamic_allocator::deallocate`

## Description

Deallocates a memory block of the requested size.

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

The function calls `operator delete`, effectively delegating the deallocation task to the operating system.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)