# `dynamic_allocator::(destructor)`

## Description

Destroys a `dynamic_allocator` object.

## Syntax

```cpp
~dynamic_allocator() noexcept override;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the allocator is stateless, it does not perform any cleanups; thus, the destructor is trivial.

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)