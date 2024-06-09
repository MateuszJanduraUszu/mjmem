# `pool_exhausted`

## Description

> **Removed**: This class has been removed from the library since version 1.0.1.

Defines an exception that is raised when a pool is exhausted.

## Syntax

```cpp
class pool_exhausted {
public:
    pool_exhausted() noexcept;
    ~pool_exhausted() noexcept;

    [[noreturn]] static void raise();
};
```

## Member types

(none)

## Member functions

- [(constructor)](pool_exhausted-ctor.md)
- [(destructor)](pool_exhausted-dtor.md)
- [raise](pool_exhausted-raise.md)

## Member constants

(none)

## Non-member functions

(none)

## Remarks

The `pool_exhausted` class is not intended for copying, moving, or assigning. It serves as a type for catching pool exhausted exceptions.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<exception.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `1.0.0`           |

## See also

- [allocation_failure](allocation_failure.md)
- [allocation_limit_exceeded](allocation_limit_exceeded.md)
- [resource_overrun](resource_overrun.md)