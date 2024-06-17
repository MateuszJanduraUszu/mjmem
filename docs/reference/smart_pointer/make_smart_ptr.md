# `make_smart_ptr`

## Description

Creates a new `smart_ptr` object that holds a pointer created from the given arguments.

## Syntax

```cpp
template <class _Ty, class... _Types>
smart_ptr<_Ty> make_smart_ptr(_Types&&... _Args);
```

## Parameters

- `_Args...`: The arguments to create the pointer from.

## Return value

Returns the created smart pointer.

## Exceptions

May throw a specific exception if the allocation or reference counter construction fails.

## Remarks

The function creates a new `smart_ptr` object and assigns a pointer that is created by calling 
[create_object](../object_allocator/create_object.md) with the given arguments.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)