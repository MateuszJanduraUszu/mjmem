# `operator==` (`smart_ptr`)

## Description

Compares two smart pointers for equality.

## Syntax

```cpp
template <class _Ty>
bool operator==(const smart_ptr<_Ty>& _Left, const smart_ptr<_Ty>& _Right) noexcept;

template <class _Ty>
bool operator==(const smart_ptr<_Ty>& _Left, nullptr_t) noexcept;
```

## Parameters

- `_Left`: The left-side smart pointer to compare.
- `_Right`: The right-side smart pointer to compare.

## Return value

Returns true if the two smart pointers are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function compares the stored pointers of the two `smart_ptr` instances for equality. The `nullptr_t` variant checks if the stored pointer 
is null. These are equivalents to:

```cpp
_Left.get() == _Right.get();
!_Left;
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)