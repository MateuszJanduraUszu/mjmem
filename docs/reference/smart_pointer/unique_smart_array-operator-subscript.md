# `unique_smart_array::operator[]`

## Description

Retrieves the requested element from the stored array.

## Syntax

```cpp
element_type& operator[](const size_t _Idx) const;
```

## Parameters

- `_Idx`: The index of the element.

## Return value

Returns a read-only reference to the requested element.

## Exceptions

Throws [resource_overrun](../exception/resource_overrun.md) if the index `_Idx` is greater than or equal to the size of the array.

## Remarks

The function accesses the requested element with bounds checking to ensure safety. It is equivalent to:

```cpp
get()[_Idx];
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)