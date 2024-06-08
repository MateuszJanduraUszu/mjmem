# `allocation_limit_exceeded::raise`

## Description

Raises an `allocation_limit_exceeded` exception.

## Syntax

```cpp
[[noreturn]] static void raise();
```

## Parameters

(none)

## Return value

(none)

## Exceptions

The function throws an `allocation_limit_exceeded` exception.

## Remarks

The function is designed to throw its type for consistency and to avoid defining additional functions with similar behavior. Its behavior is 
equivalent to `throw allocation_limit_exceeded()`. The use of the **noreturn** attribute indicates that the function does not return to the 
execution path.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<exception.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocation_limit_exceeded](allocation_limit_exceeded.md)