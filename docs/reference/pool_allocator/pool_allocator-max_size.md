# `pool_allocator::max_size`

## Description

Retrieves the maximum supported allocation size.

## Syntax

```cpp
size_type max_size() const noexcept override;
```

## Parameters

(none)

## Return value

Returns the maximum supported allocation size.

## Exceptions

(none)

## Remarks

The maximum allocation size is determined during initialization. The function returns the minimum value between the maximum 
allocation size set during initialization and the size of the associated resource. This ensures that the maximum allocation size does not 
exceed the available memory in the associated resource.

## Requirements

| Requirement             | Value                  |
|-------------------------|------------------------|
| Include header          | `<pool_allocator.hpp>` |
| Minimum library version | `1.0.0`                |
| Maximum library version | `N/A`                  |

## See also

- [pool_allocator](pool_allocator.md)