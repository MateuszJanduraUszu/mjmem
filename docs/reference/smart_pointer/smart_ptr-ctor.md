# `smart_ptr::(constructor)`

## Description

Creates a new `smart_ptr` object.

## Syntax

```cpp
smart_ptr() noexcept;
smart_ptr(const smart_ptr& _Other) noexcept;
smart_ptr(smart_ptr&& _Other) noexcept;
smart_ptr(nullptr_t) noexcept;
explicit smart_ptr(pointer _Ptr);
smart_ptr(unique_smart_ptr<_Ty>&& _Sptr);
```

## Parameters

- `_Other`: The smart pointer to construct with.
- `_Ptr`: The pointer to construct with.
- `_Sptr`: The unique smart pointer to construct with.

## Return value

(none)

## Exceptions

May throw a specific exception if the resource counter creation fails.

## Remarks

The constructors create a new `smart_ptr` object. The default and `nullptr_t` constructors create an empty smart pointer which stores a 
null pointer, with no refernce counter created. The copy constructor assigns the pointer stored by `_Other` and increments the reference 
counter. The move constructor transfters the pointer and the counter from `_Other` without altering the reference counter. The `pointer` 
and `unique_smart_ptr` constructors create a new smart pointer and assign the specified pointer, with a reference counter created. The 
`unique_smart_ptr` constructor transfers the pointer via `_Sptr.release()`.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)