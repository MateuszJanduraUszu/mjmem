# `smart_array::operator->`

## Description

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

The function returns the stored array. Unlike [smart_ptr::operator->](smart_ptr-operator-arrow.md), this function does not access the 
object because the class stores an array, not a pointer to an object. The operator is defined for consistency with smart pointers.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)