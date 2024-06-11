# `allocate_object_array_using_allocator`

## Description

Allocates memory for the requested number of objects using the specified allocator.

## Syntax

```cpp
template <class _Ty, compatible_allocator _Alloc>
_Ty* allocate_object_array_using_allocator(const size_t _Count, _Alloc& _Al);
```

## Parameters

- `_Count`: The number of objects to allocate space for.
- `_Al`: A reference to the allocator used to allocate memory.

## Return value

Returns an array of allocated objects.

## Exceptions

May throw a specific exception if the allocation fails.

## Remarks

The function allocates memory for the objects with the specified allocator but does not initialize them.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.2`                  |
| Maximum library version | `N/A`                    |

## See also

- [allocate_object_array](allocate_object_array.md)
- [compatible_allocator](compatible_allocator.md)
- [create_object](create_object.md)
- [create_object_using_allocator](create_object_using_allocator.md)
- [delete_object](delete_object.md)
- [delete_object_array](delete_object_array.md)
- [delete_object_array_using_allocator](delete_object_array_using_allocator.md)
- [delete_object_using_allocator](delete_object_using_allocator.md)