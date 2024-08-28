# `swap_endian`

## Description

Reverses the bytes of an integer. 

## Syntax

```cpp
template <integral _Ty>
constexpr _Ty swap_endian(const _Ty _Value) noexcept;
```

## Parameters

- `_Value`: The integer whose bytes will be reversed.

## Return value

Returns the integer with its bytes reversed.

## Exceptions

(none)

## Remarks

The function reverses the bytes of the given integer. This is useful for converting between different endianness formats. Ensure that this 
function is used appropriately in contexts where endianness needs to be adjusted, as improper use could lead to unexpected results.

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
- [to_big_endian](to_big_endian.md)
- [to_little_endian](to_little_endian.md)