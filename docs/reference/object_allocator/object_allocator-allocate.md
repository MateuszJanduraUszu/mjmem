# `object_allocator::allocate`

## Description

Allocates memory for a requested number of objects.

## Syntax

```cpp
pointer allocate(const size_type _Count);
```

## Parameters

- `_Count`: The number of objects to allocate space for.

## Return value

Returns a pointer to the allocated memory block if successful; otherwise, returns a null pointer.

## Exceptions

May throw a specific exception if the allocation fails.

## Remarks

The allocator effectively calls the global allocator's `allocate`. However, since the global allocator's allocation size is in bytes, the value is 
adjusted by multiplying it by the size of the selected type. The call is equivalent to:

```cpp
static_cast<pointer>(get_allocator().allocate(_Count * sizeof(_Ty)));
```

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)