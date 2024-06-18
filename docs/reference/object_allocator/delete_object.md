# `delete_object`

## Description

Deletes an object.

## Syntax

```cpp
template <class _Ty>
void delete_object(_Ty* const _Obj) noexcept(<expr>);
```

## Parameters

- `_Obj`: A pointer to the object to delete.

## Return value

(none)

## Exceptions

May throw a specific exception if the object destruction fails.

## Remarks

The function deallocates the memory occupied by the object. If the object's type is not trivial, it calls the destructor first. To deallocate memory, the global allocator is used. The function is marked as **noexcept** if the following expression evaluates to true:

```cpp
std::is_nothrow_destructible_v<_Ty>
```

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [allocate_object_array](allocate_object_array.md)
- [allocate_object_array_using_allocator](allocate_object_array_using_allocator.md)
- [create_object](create_object.md)
- [create_object_using_allocator](create_object_using_allocator.md)
- [delete_object_array](delete_object_array.md)
- [delete_object_array_using_allocator](delete_object_array_using_allocator.md)
- [delete_object_using_allocator](delete_object_using_allocator.md)