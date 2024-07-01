# `block_allocator::block_size`

## Description

Retrieves the allocation block size.

## Syntax

```cpp
size_type block_size() const noexcept;
```

## Parameters

(none)

## Return value

Returns the allocation block size.

## Exceptions

(none)

## Remarks

The function returns the allocation block size, which is the smallest allocation unit. The block size is set in the allocator constructor and 
cannot be changed.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `2.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)