# `synchronized_allocator::max_size`

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

The function internally calls the associated allocator's `max_size` function in a locked context, ensuring thread-safe access.

## Requirements

| Requirement             | Value                          |
|-------------------------|--------------------------------|
| Include header          | `<synchronized_allocator.hpp>` |
| Minimum library version | `1.0.0`                        |
| Maximum library version | `N/A`                          |

## See also

- [synchronized_allocator](synchronized_allocator.md)