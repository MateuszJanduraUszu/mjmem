# `resource_overrun::raise`

## Description

Raises a `resource_overrun` exception.

## Syntax

```cpp
[[noreturn]] static void raise();
```

## Parameters

(none)

## Return value

(none)

## Exceptions

Throws `resource_overrun`.

## Remarks

The function is designed to throw its type for consistency and to avoid defining additional functions with similar behavior. Its behavior is 
equivalent to `throw resource_overrun()`. The use of the **noreturn** attribute indicates that the function does not return to the 
execution path.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<exception.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [resource_overrun](resource_overrun.md)