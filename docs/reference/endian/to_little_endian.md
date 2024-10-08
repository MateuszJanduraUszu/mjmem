# `to_little_endian`

## Description

Converts an integer from the host endianness to little-endian format. 

## Syntax

```cpp
template <integral _Ty>
constexpr _Ty to_little_endian(const _Ty _Value) noexcept;
```

## Parameters

- `_Value`: The integer whose endianness will be converted to little-endian.

## Return value

Returns the integer in little-endian format.

## Exceptions

(none)

## Remarks

The function is used to convert an integer to little-endian format. If the host system is little-endian, the function does nothing and 
returns the input value as is. If the host system is big-endian, the function converts the value to little-endian format by reversing the byte 
order.

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
- [integral](integral.md)
- [swap_endian](swap_endian.md)
- [to_big_endian](to_big_endian.md)