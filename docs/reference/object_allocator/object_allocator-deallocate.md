# `object_allocator::deallocate`

## Description

Deallocates a requested number of objects.

## Syntax

```cpp
void deallocate(pointer _Ptr, const size_type _Count) noexcept;
```

## Parameters

- `_Ptr`: The array of objects to deallocate.
- `_Count`: The number of objects in the array.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function effectively calls the global allocator's `deallocate`. However, since the global allocator's allocation size is in bytes, the value 
is adjusted by multiplying it by the size of the selected type. The call is equivalent to:

```cpp
get_allocator().deallocate(_Ptr, _Count * sizeof(_Ty));
```

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)