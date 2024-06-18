# `unique_smart_array::release`

## Description

Exchanges the stored array to a null pointer.

## Syntax

```cpp
array release() noexcept;
```

## Parameters

(none)

## Return value

Returns the stored array.

## Exceptions

(none)

## Remarks

The function exchanges the stored array and size with a null pointer and zero, then returns the old array along with its size. Note that if 
you do not assign the returned array to any variable, it will be impossible to recover it.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)