# `operator==` (`smart_array`)

## Description

Compares two smart pointers fo equality.

## Syntax

```cpp
template <class _Ty>
bool operator==(const smart_array<_Ty>& _Left, const smart_array<_Ty>& _Right) noexcept;

template <class _Ty>
bool operator==(const smart_array<_Ty>& _Left, nullptr_t) noexcept;
```

## Parameters

- `_Left`: The left-side smart pointer to compare.
- `_Right`: The right-side smart pointer to compare.

## Return value

Returns true if the two smart pointers are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function compares the stored arrays of the two `smart_array` instances for equality. The second function checks whether the smart 
pointer stores a null array.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)