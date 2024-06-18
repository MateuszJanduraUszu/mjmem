# `smart_array::(constructor)`

## Description

Creates a new `smart_array` object.

## Syntax

```cpp
smart_array() noexcept;
smart_array(const smart_array& _Other) noexcept;
smart_array(smart_array&& _Other) noexcept;
smart_array(nullptr_t) noexcept;
smart_array(pointer _Ptr, const size_t _Size);
smart_array(unique_smart_array<_Ty>&& _Sarr);
```

## Parameters

- `_Other`: The smart pointer to move construct with.
- `_Ptr`: The array to assign.
- `_Size`: The size of the array.
- `_Sarr`: The unique smart pointer to construct with.

## Return value

(none)

## Exceptions

May throw a specific exception if the resource counter creation fails.

## Remarks

The constructors create a new `smart_array` object. The default and `nullptr_t` constructors create an empty smart pointer which stores a 
null array, with no reference counter created. The copy constructor assigns the array stored by `_Other` and increments the reference 
counter. The move constructor transfers the array and the counter from `_Other` without altering the reference counter. The 
`pointer`/`size_t` and `unique_smart_array` constructors create a new smart pointer and assign the specified array, with a reference 
counter created. The `unique_smart_array` constructor transfers the array via `_Sarr.release()`.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)