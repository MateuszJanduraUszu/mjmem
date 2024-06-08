# `allocation_failure`

## Description

Defines an exception that is raised on allocation failure.

## Syntax

```cpp
class allocation_failure {
public:
    allocation_failure() noexcept;
    ~allocation_failure() noexcept;

    [[noreturn]] static void raise();
};
```

## Member types

(none)

## Member functions

- [(constructor)](allocation_failure-ctor.md)
- [(destructor)](allocation_failure-dtor.md)
- [raise](allocation_failure-raise.md)

## Non-member functions

(none)

## Remarks

The `allocation_failure` class is not intended for copying, moving, or assigning. It serves as a type for catching allocation failure 
exceptions.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<exception.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocation_limit_exceeded](allocation_limit_exceeded.md)
- [resource_overrun](resource_overrun.md)