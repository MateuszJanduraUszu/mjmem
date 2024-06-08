# `dynamic_allocator::max_size`

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

The maximum supported allocation size is the one which will fit in `size_type`, equivalent to `static_cast<size_type>(-1)` or 
`std::numeric_limits<size_type>::max()`.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)