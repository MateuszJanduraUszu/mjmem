# `optimized_pair::swap`

## Description

Swaps two pairs.

## Syntax

```cpp
void swap(optimized_pair& _Other) noexcept(<expr>);
```

## Parameters

- `_Other`: The pair to swap with.

## Return value

(none)

## Exceptions

May throw a specific exception if the construction or assignment fails.

## Remarks

The function swaps the members of two pairs. It is marked as **noexcept** if the following expression evaluates to true:

```cpp
std::is_nothrow_swappable_v<_Ty1> && std::is_nothrow_swappable_v<_Ty2>
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)