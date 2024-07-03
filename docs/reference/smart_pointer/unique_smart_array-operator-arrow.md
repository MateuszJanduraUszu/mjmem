# `unique_smart_array::operator->`

## Description

> **Important**: This function has been deprecated and removed from the library since version 2.0.0.

Retrieves the stored array.

## Syntax

```cpp
pointer operator->() const noexcept;
```

## Parameters

(none)

## Return value

Returns the stored array.

## Exceptions

(none)

## Remarks

The function returns the stored array. Unlike [unique_smart_ptr::operator->](unique_smart_ptr-operator-arrow.md), this function does 
not access the object because the class stores an array, not a pointer to an object. The operator is defined for consistency with smart 
pointers.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `1.0.2`               |

## See also

- [unique_smart_array](unique_smart_array.md)