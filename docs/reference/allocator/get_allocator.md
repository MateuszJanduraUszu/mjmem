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

The function returns a reference to the global allocator. It is guaranteed to succeed.

## Exceptions

(none)

## Remarks

By default, the global allocator is a [dynamic_allocator](dynamic_allocator.md). If you wish to modify it, you can use the [set_allocator](set_allocator.md) function.

## Requirements

| Requirement     | Value             |
|-----------------|-------------------|
| Include header  | `<allocator.hpp>` |
| Library version | `1.0.0` or higher |

## See also

- [allocator](allocator.md)
- [set_allocator](set_allocator.md)