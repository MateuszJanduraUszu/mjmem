# `operator==` (`unique_smart_ptr`)

## Description

Compares two smart pointers for equality.

## Syntax

```cpp
template <class _Ty>
bool operator==(const unique_smart_ptr<_Ty>& _Left, const unique_smart_ptr<_Ty>& _Right) noexcept;

template <class _Ty>
bool operator==(const unique_smart_ptr<_Ty>& _Left, nullptr_t) noexcept;
```

## Parameters

- `_Left`: The left-side smart pointer to compare.
- `_Right`: The right-side smart pointer to compare.

## Return value

Returns true if the two smart pointers are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function compares the stored pointers of the two `unique_smart_ptr` instances for equality. The second function checks whether the 
smart pointer stores a null pointer.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)