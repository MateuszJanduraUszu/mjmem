# `allocate_object_array`

## Description

Allocates memory for the requested number of objects.

## Syntax

```cpp
template <class _Ty>
_Ty* allocate_object_array(const size_t _Count);
```

## Parameters

- `_Count`: The number of objects to allocate space for.

## Return value

Returns an array of allocated objects.

## Exceptions

May throw a specific exception if the allocation fails.

## Remarks

The function allocates memory for the objects but does not initialize them. To allocate memory, the global allocator is used; therefore, it 
is not specified which exception is thrown if the allocation fails.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [allocate_object_array_using_allocator](allocate_object_array_using_allocator.md)
- [create_object](create_object.md)
- [create_object_using_allocator](create_object_using_allocator.md)
- [delete_object](delete_object.md)
- [delete_object_array](delete_object_array.md)
- [delete_object_array_using_allocator](delete_object_array_using_allocator.md)
- [delete_object_using_allocator](delete_object_using_allocator.md)