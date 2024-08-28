# `integral`

## Description

Defines a concept that checks whether the specified type is an integral type.

## Syntax

```cpp
template <class _Ty>
concept integral = std::disjunction_v<::std::is_integral<_Ty>
#ifdef _MJX_INT128_SUPPORTED
    , std::is_same<_Ty, int128_t>, std::is_same<_Ty, uint128_t>
#endif // _MJX_INT128_SUPPORTED
>;
```

## Remarks

The specified type is considered integral if `std::is_integral` evaluates to true for it. If 128-bit integer types are supported, the concept 
also considers `int128_t` and `uint128_t` as integral types.

## Requirements

| Requirement             | Value          |
|-------------------------|----------------|
| Include header          | `<endian.hpp>` |
| Minimum library version | `2.1.0`        |
| Maximum library version | `N/A`          |

## See also

- [endian](endian.md)
- [from_big_endian](from_big_endian.md)
- [from_little_endian](from_little_endian.md)
- [to_big_endian](to_big_endian.md)
- [to_little_endian](to_little_endian.md)
- [swap_endian](swap_endian.md)