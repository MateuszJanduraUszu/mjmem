# `allocation_failure::raise`

## Description

Raises an `allocation_failure` exception.

## Syntax

```cpp
[[noreturn]] static void raise();
```

## Parameters

(none)

## Return value

(none)

## Exceptions

Throws `allocation_failure`.

## Remarks

The function is designed to throw its type for consistency and to avoid defining additional functions with similar behavior. The use of the 
**noreturn** attribute indicates that the function does not return to the execution path. It is equivalent to:

```cpp
throw allocation_failure();
```

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<exception.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocation_failure](allocation_failure.md)