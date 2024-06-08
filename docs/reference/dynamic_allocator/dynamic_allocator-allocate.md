# `dynamic_allocator::allocate`

## Description

Allocates a requested number of bytes.

## Syntax

```cpp
pointer allocate(const size_type _Count) override;
```

## Parameters

- `_Count`: The number of bytes to allocate.

## Return value

Returns a pointer to the allocated block if successful; otherwise, returns a null pointer.

## Exceptions

Throws [allocation_failure](../exception/allocation_failure.md) if the allocation fails.

## Remarks

The function calls `operator new`, effectively delegating the allocation task to the operating system.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)