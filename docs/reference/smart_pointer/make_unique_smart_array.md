# `make_unique_smart_array`

## Description

Creates a new `unique_smart_array` object that holds an allocated array.

## Syntax

```cpp
template <class _Ty>
unique_smart_array<_Ty> make_unique_smart_array(const size_t _Size);
```

## Parameters

- `_Size`: The size of the array.

## Return value

Returns the created smart pointer.

## Exceptions

May throw a specific exception if the allocation fails.

## Remarks

The function creates a new `unique_smart_array` object and assigns an array that is allocated by calling 
[allocate_object_array](../object_allocator/allocate_object_array.md) with the given size.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)