# `allocation_limit_exceeded`

## Description

Defines an exception that is raised when the allocation limit is exceeded.

## Syntax

```cpp
class allocation_limit_exceeded {
public:
    allocation_limit_exceeded() noexcept;
    ~allocation_limit_exceeded() noexcept;

    [[noreturn]] static void raise();
};
```

## Member types

(none)

## Member functions

- [(constructor)](allocation_limit_exceeded-ctor.md)
- [(destructor)](allocation_limit_exceeded-dtor.md)
- [raise](allocation_limit_exceeded-raise.md)

## Non-member functions

(none)

## Remarks

The `allocation_limit_exceeded` class is not intended for copying, moving, or assigning. It serves as a type for catching allocation limit 
exceeded exceptions.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<exception.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocation_failure](allocation_failure.md)
- [resource_overrun](resource_overrun.md)