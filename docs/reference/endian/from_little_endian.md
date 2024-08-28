# `from_little_endian`

## Description

Converts an integer from little-endian format to the host endianness. 

## Syntax

```cpp
template <integral _Ty>
constexpr _Ty from_little_endian(const _Ty _Value) noexcept;
```

## Parameters

- `_Value`: The integer in little-endian format that will be converted to the host endianness.

## Return value

Returns the integer in the host endianness format.

## Exceptions

(none)

## Remarks

The function converts an integer from little-endian format to the endianness used by the host system. If the host system is little-endian, 
the function does nothing and returns the input value unchanged. If the host system is big-endian, the function reverses the byte order 
to convert the value from little-endian format to big-endian format.

## Requirements

| Requirement             | Value          |
|-------------------------|----------------|
| Include header          | `<endian.hpp>` |
| Minimum library version | `2.1.0`        |
| Maximum library version | `N/A`          |

## See also

- [endian](endian.md)
- [from_big_endian](from_big_endian.md)
- [integral](integral.md)
- [to_big_endian](to_big_endian.md)
- [to_little_endian](to_little_endian.md)
- [swap_endian](swap_endian.md)