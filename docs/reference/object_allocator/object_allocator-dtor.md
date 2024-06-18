# `object_allocator::(destructor)`

## Description

Destroys an `object_allocator` object.

## Syntax

```cpp
~object_allocator() noexcept = default;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the allocator is stateless, it does not perform any cleanup actions. Therefore, the destructor is trivial.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)