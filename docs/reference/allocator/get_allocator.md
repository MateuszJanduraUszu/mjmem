# `get_allocator`

## Description

Retrieves a reference to the global allocator.

## Syntax

```cpp
allocator& get_allocator() noexcept;
```

## Parameters

(none)

## Return value

Returns a reference to the global allocator.

## Exceptions

(none)

## Remarks

By default, the global allocator is a [dynamic_allocator](../dynamic_allocator/dynamic_allocator.md). If you wish to modify it, you can use the [set_allocator](set_allocator.md) function.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<allocator.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocator](allocator.md)
- [set_allocator](set_allocator.md)