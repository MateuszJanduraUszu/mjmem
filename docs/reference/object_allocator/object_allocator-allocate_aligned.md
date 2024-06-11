# `object_allocator::allocate_aligned`

## Description

Allocates memory for a requested number of objects aligned to the requested alignment.

## Syntax

```cpp
pointer allocate_aligned(const size_type _Count, const size_type _Align);
```

## Parameters

- `_Count`: The number of objects to allocate space for.
- `_Align`: The requested alignment.

## Return value

Returns a pointer to the memory block if successful; otherwise, returns a null pointer.

## Exceptions

May throw a specific exception if the allocation fails.

## Remarks

The allocator effectively calls the global allocator's `allocate_aligned`. However, since the global allocator's allocation size is in bytes, the 
value is adjusted by multiplying it by the size of the selected type. The call is equivalent to:

```cpp
get_allocator().allocate_aligned(_Count * sizeof(_Ty), _Align);
```

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)