# `pool_exhausted::raise`

## Description

Raises a `pool_exhausted` exception.

## Syntax

```cpp
[[noreturn]] static void raise();
```

## Parameters

(none)

## Return value

(none)

## Exceptions

Throws `pool_exhausted`.

## Remarks

The function is designed to throw its type for consistency and to avoid defining additional functions with similar behavior. Its behavior is 
equivalent to `throw pool_exhausted()`. The use of the **noreturn** attribute indicates that the function does not return to the execution 
path.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<exception.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `1.0.0`           |

## See also

- [pool_exhausted](pool_exhausted.md)