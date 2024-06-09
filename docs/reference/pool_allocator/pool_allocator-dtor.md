# `pool_allocator::(destructor)`

## Description

Destroys a `pool_allocator` object.

## Syntax

```cpp
~pool_allocator() noexcept override;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the allocator is stateful, it must be uninitialized. When called, it destroys the list of free blocks, ensuring all resources are properly 
released. Note that the associated resource is not destroyed, as the allocator stores it as a reference to the user-provided resource.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [pool_allocator](pool_allocator.md)