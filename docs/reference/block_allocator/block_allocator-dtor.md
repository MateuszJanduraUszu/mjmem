# `block_allocator::(destructor)`

## Description

Destroys a `block_allocator` object.

## Syntax

```cpp
~block_allocator() noexcept override;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the allocator is stateful, it deallocates the bitmap. However it does not destroy the associated resource, which is stored as a 
reference to the user-provided resource.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `1.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)