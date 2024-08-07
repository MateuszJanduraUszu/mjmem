# `unique_smart_array::operator*`

## Description

> **Important**: This function has been deprecated and removed from the library since version 2.0.0.

Retrieves the first element of the stored array.

## Syntax

```cpp
element_type& operator*() const noexcept;
```

## Parameters

(none)

## Return value

Returns a read-only reference to the first element of the stored array.

## Exceptions

(none)

## Remarks

The function returns the first element of the stored array. The behavior is undefined if the stored array is null. Unlike 
[unique_smart_ptr::operator*](unique_smart_ptr-operator-deref.md), this function does not dereference the pointer because the class 
stores an array, not a pointer to an object. The operator is defined for consistency with smart pointers. It is equivalent to:

```cpp
*get();
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `1.0.2`               |

## See also

- [unique_smart_array](unique_smart_array.md)