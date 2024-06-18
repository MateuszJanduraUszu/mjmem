# `optimized_pair::(constructor)`

## Description

Creates a new `optimized_pair` object.

## Syntax

```cpp
optimized_pair() noexcept(<expr>);
optimized_pair(const _Ty1& _Val1, const _Ty2& _Val2) noexcept(<expr>);
optimized_pair(_Ty1&& _Val1, const _Ty2&& _Val2) noexcept(<expr>);

optimized_pair(const optimized_pair&) = default;
optimized_pair(optimized_pair&&)      = default;
```

## Parameters

- `_Val1`: The value to construct `_Ty1` from.
- `_Val2`: The value to construct `_Ty2` from.

## Return value

(none)

## Exceptions

May throw a specific exception if the copy/move fails.

## Remarks

The function constructs `_Ty1` and `_Ty2` with the given arguments. The constructors are marked as **noexcept** if the following 
expressions evaluate to true:

- ```cpp
  std::is_nothrow_default_constructible_v<_Ty1> && std::is_nothrow_default_constructible_v<_Ty2>
  ```
- ```cpp
  std::is_nothrow_copy_constructible_v<_Ty1> && std::is_nothrow_copy_constructible_v<_Ty2>
  ```
- ```cpp
  std::is_nothrow_move_constructible_v<_Ty1> && std::is_nothrow_move_constructible_v<_Ty2>
  ```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)