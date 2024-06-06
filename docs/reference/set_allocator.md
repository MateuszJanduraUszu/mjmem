# `set_allocator`

## Description

Modifies the global allocator.

## Syntax

```cpp
_MJMEM_API void set_allocator(allocator& _New_al) noexcept;
```

## Parameters

* `_New_al`: A reference to the new allocator.

## Return value

The function does not return any value.

## Exceptions

The function does not throw any exceptions.

## Remarks

The function replaces the current global allocator with the new allocator provided. To exchange the current allocator, you should call [get_allocator](get_allocator.md) first to retrieve the existing allocator, if needed.

## Requirements

| Requirement     | Value             |
|-----------------|-------------------|
| Include header  | `<allocator.hpp>` |
| Library version | `1.0.0` or higher |

## See also

- [allocator](allocator.md)
- [get_allocator](get_allocator.md)