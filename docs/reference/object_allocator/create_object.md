# `create_object`

## Description

Creates a new object of a specified type.

## Syntax

```cpp
template <class _Ty, class... _Types>
_Ty* create_object(_Types&&... _Args);
```

## Parameters

- `_Args...`: The arguments used to construct `_Ty`.

## Return value

Returns a pointer to the created object.

## Exceptions

May throw a specific exception if the allocation or object construction fails.

## Remarks

The function first allocates memory for the object, then initializes it with the specified arguments. To allocate memory, the global 
allocator is used; therefore, it is not specified which exception is thrown if the allocation fails.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [allocate_object_array](allocate_object_array.md)
- [allocate_object_array_using_allocator](allocate_object_array_using_allocator.md)
- [create_object_using_allocator](create_object_using_allocator.md)
- [delete_object](delete_object.md)
- [delete_object_array](delete_object_array.md)
- [delete_object_array_using_allocator](delete_object_array_using_allocator.md)
- [delete_object_using_allocator](delete_object_using_allocator.md)