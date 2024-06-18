# `operator==` (`optimized_pair`)

## Description

Compares two pairs for equality.

## Syntax

```cpp
template <class _Ty1, class _Ty2>
bool operator==(const optimized_pair<_Ty1, _Ty2>& _Left, const optimized_pair<_Ty1, _Ty2>& _Right);
```

## Parameters

- `_Left`: The left-side pair to compare.
- `_Right`: The right-side pair to compare.

## Return value

Returns true if the two pairs are equal; otherwise, returns false.

## Exceptions

May throw a specific exception if the comparison fails.

## Remarks

The function compares the members of the pairs. The call is equivalent to:

```cpp
_Left.first() == _Right.first() && _Left.second() == _Right.second();
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)