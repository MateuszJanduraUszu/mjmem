# `create_object_using_allocator`

## Description

Creates a new object of a specified type using the specified allocator.

## Syntax

```cpp
template <class _Ty, compatible_allocator _Alloc, class... _Types>
_Ty* create_object_using_allocator(_Alloc& _Al, _Types&&... _Args);
```

## Parameters

- `_Al`: A reference to the allocator used to allocate memory.
- `_Args...`: The arguments used to construct `_Ty`.

## Return value

Returns a pointer to the created object.

## Exceptions

May throw a specific exception during memory allocation or object construction.

## Remarks

The function first allocates memory with the specifed allocator for the object, then initializes it with the specified arguments.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.2`                  |
| Maximum library version | `N/A`                    |

## See also

- [allocate_object_array](allocate_object_array.md)
- [allocate_object_array_using_allocator](allocate_object_array_using_allocator.md)
- [compatible_allocator](compatible_allocator.md)
- [create_object](create_object.md)
- [delete_object](delete_object.md)
- [delete_object_array](delete_object_array.md)
- [delete_object_array_using_allocator](delete_object_array_using_allocator.md)
- [delete_object_using_allocator](delete_object_using_allocator.md)