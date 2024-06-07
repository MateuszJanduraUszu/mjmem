# `resource_overrun`

## Description

Defines an exception that is raised when a resource is accessed outside its bounds.

## Syntax

```cpp
class resource_overrun {
public:
    resource_overrun() noexcept;
    ~resource_overrun() noexcept;

    [[noreturn]] static void raise();
};
```

## Member types

(none)

## Member functions

- [(constructor)](resource_overrun-ctor.md)
- [(destructor)](resource_overrun-dtor.md)
- [raise](resource_overrun-raise.md)

## Non-member functions

(none)

## Remarks

The `resource_overrun` class is not intended for copying, moving, or assigning. It serves as a type for catching resource overrun exceptions.

## Requirements

| Requirement     | Value             |
|-----------------|-------------------|
| Include header  | `<exception.hpp>` |
| Library version | `1.0.0` or newer  |

## See also

- [allocation_failure](allocation_failure.md)
- [allocation_limit_exceeded](allocation_limit_exceeded.md)