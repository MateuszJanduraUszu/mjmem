# `delete_object_using_allocator`

## Description

Deletes an object using the specified allocator.

## Syntax

```cpp
template <class _Ty, compatible_allocator _Alloc>
void delete_object_using_allocator(_Ty* const _Obj, _Alloc& _Al) noexcept(<expr>);
```

## Parameters

- `_Obj`: A pointer to the object to delete.
- `_Al`: A reference to the allocator used to deallocate memory.

## Return value

(none)

## Exceptions

May throw a specific exception if the object destruction fails.

## Remarks

The function deallocates the memory occupied by the object with the specified allocator. If the object's type is not trivial, it calls the 
destructor first. The function is marked as **noexcept** if the following expression evaluates to true:

```cpp
std::is_nothrow_destructible_v<_Ty>
```

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
- [create_object_using_allocator](create_object_using_allocator.md)
- [delete_object](delete_object.md)
- [delete_object_array](delete_object_array.md)
- [delete_object_array_using_allocator](delete_object_array_using_allocator.md)