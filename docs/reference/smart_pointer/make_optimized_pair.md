# `make_optimized_pair`

## Description

Creates a new `optimized_pair` object from the given arguments.

## Syntax

```cpp
template <class _Ty1, class _Ty2>
optimized_pair<_Ty1, _Ty2> make_optimized_pair(_Ty1&& _Val1, _Ty2&& _Val2) noexcept(<expr>);
```

## Parameters

- `_Val1`: The value to construct `_Ty1`.
- `_Val2`: The value to construct `_Ty2`.

## Return value

Returns the created pair.

## Exceptions

May throw a specific exception during members construction.

## Remarks

The function creates a new pair with `_Ty1` and `_Ty2` members. It is an equivalent to calling the move constructor. The given arguments 
are forwarded as rvalue references to the move constructor where the members will be constructed.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)