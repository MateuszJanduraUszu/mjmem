# `block_allocator::max_size`

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

The maximum supported size is determinated by the size of the associated resource. Since the maximum block size cannot exceed the 
associated resource's size, the `max_size` function simply returns the size of the associated resource. Internally, it is equivalent to 
`_Resource.size()`, where `_Resource` is a reference to the resource passed while constructing the allocator.

## Requirements

| Requirement             | Value                   |
|-------------------------|-------------------------|
| Include header          | `<block_allocator.hpp>` |
| Minimum library version | `1.0.0`                 |
| Maximum library version | `N/A`                   |

## See also

- [block_allocator](block_allocator.md)