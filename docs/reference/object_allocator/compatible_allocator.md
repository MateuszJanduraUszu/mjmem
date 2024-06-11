# `compatible_allocator`

## Description

Defines a concept that checks whether the specified allocator is compatible with the predefined ones.

## Syntax

```cpp
template <class _Alloc>
concept compatible_allocator = std::is_base_of_v<allocator, _Alloc>;
```

## Remarks

The specified allocator is considered compatible with the predefined ones if it implements the [allocator](../allocator/allocator.md) interface. This feature is especially useful when requiring the specified allocator to behave the same as the predefined ones.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.2`                  |
| Maximum library version | `N/A`                    |

## See also

- [allocate_object_array_using_allocator](allocate_object_array_using_allocator.md)
- [create_object_using_allocator](create_object_using_allocator.md)
- [delete_object_array_using_allocator](delete_object_array_using_allocator.md)
- [delete_object_using_allocator](delete_object_using_allocator.md)