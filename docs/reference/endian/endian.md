# `endian`

## Description

Defines endianness formats, including the host endianness.

## Syntax

```cpp
enum class endian : unsigned char {
    little = 0,
    big    = 1,
#ifdef _MJX_LITTLE_ENDIAN
    native = little
#else // ^^^ _MJX_LITTLE_ENDIAN ^^^ / vvv _MJX_BIG_ENDIAN vvv
    native = big
#endif // _MJX_LITTLE_ENDIAN
};
```

## Remarks

The enumeration includes `little`, `big`, and `native` values. The `native` value represents the host system's endianness: `little` if the host is 
little-endian, or `big` if the host is big-endian.

## Requirements

| Requirement             | Value          |
|-------------------------|----------------|
| Include header          | `<endian.hpp>` |
| Minimum library version | `2.1.0`        |
| Maximum library version | `N/A`          |

## See also

- [from_big_endian](from_big_endian.md)
- [from_little_endian](from_little_endian.md)
- [integral](integral.md)
- [swap_endian](swap_endian.md)
- [to_big_endian](to_big_endian.md)
- [to_little_endian](to_little_endian.md)