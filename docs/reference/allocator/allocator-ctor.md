# `allocator::(constructor)`

## Description

Creates a new allocator instance.

## Syntax

```cpp
allocator() noexcept;
allocator(const allocator& _Other) noexcept;
allocator(allocator&& _Other) noexcept;
```

## Parameters

* `_Other`: Another allocator to construct with.

## Return value

(none)

## Exceptions

(none)

## Remarks

Although the allocator is stateless, meaning that its construction have no visible effect, they are defined to avoid conflicts in derived class 
constructors. This ensures proper initialization and maintains consistency in the class hierarchy.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<allocator.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocator](allocator.md)