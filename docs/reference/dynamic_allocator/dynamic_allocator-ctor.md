# `dynamic_allocator::(constructor)`

## Description

Constructs a new `dynamic_allocator` object.

## Syntax

```cpp
dynamic_allocator() noexcept;
dynamic_allocator(const dynamic_allocator& _Other) noexcept;
dynamic_allocator(dynamic_allocator&& _Other) noexcept;
```

## Parameters

- `_Other`: An allocator to copy/move from.

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the allocator is stateless, it does not perform any initialization; thus, the constructors are trivial.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)