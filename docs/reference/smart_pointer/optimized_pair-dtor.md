# `optimized_pair::(destructor)`

## Description

Destroys an `optimized_pair` object.

## Syntax

```cpp
~optimized_pair() noexcept = default;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The destructor destroys `_Ty1` and `_Ty2`. Despite this, it is defined as trivial because it performs no additional actions beyond the default 
behavior of destroying its members.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)