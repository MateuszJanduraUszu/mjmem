# `set_allocator`

## Description

Modifies the global allocator.

## Syntax

```cpp
void set_allocator(allocator& _New_al) noexcept;
```

## Parameters

* `_New_al`: A reference to the new allocator.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function replaces the current global allocator with the new allocator provided. To exchange the current allocator, you should call 
[get_allocator](get_allocator.md) first to retrieve the existing allocator, if needed.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<allocator.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocator](allocator.md)
- [get_allocator](get_allocator.md)