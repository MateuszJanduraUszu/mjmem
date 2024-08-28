# `from_big_endian`

## Description

Converts an integer from big-endian format to the host endianness. 

## Syntax

```cpp
template <integral _Ty>
constexpr _Ty from_big_endian(const _Ty _Value) noexcept;
```

## Parameters

- `_Value`: The integer in big-endian format that will be converted to the host endianness.

## Return value

Returns the integer in the host endianness format.

## Exceptions

(none)

## Remarks

The function converts an integer from big-endian format to the endianness used by the host system. If the host system is big-endian, 
the function does nothing and returns the input value unchanged. If the host system is little-endian, the function reverses the byte order 
to convert the value from big-endian format to little-endian format.

## Requirements

| Requirement             | Value          |
|-------------------------|----------------|
| Include header          | `<endian.hpp>` |
| Minimum library version | `2.1.0`        |
| Maximum library version | `N/A`          |

## See also

- [endian](endian.md)
- [from_little_endian](from_little_endian.md)
- [integral](integral.md)
- [swap_endian](swap_endian.md)
- [to_big_endian](to_big_endian.md)
- [to_little_endian](to_little_endian.md)