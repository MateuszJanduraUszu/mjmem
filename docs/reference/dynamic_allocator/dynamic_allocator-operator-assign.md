# `dynamic_allocator::operator=`

## Description

Assigns an allocator.

## Syntax

```cpp
dynamic_allocator& operator=(const dynamic_allocator& _Other) noexcept;
dynamic_allocator& operator=(dynamic_allocator&& _Other) noexcept;
```

## Parameters

- `_Other`: The allocator to assign from.

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the allocator is stateless, the assignment operator has no visible effects; thus, the operator is trivial.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)