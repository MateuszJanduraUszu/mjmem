# `optimized_pair::operator=`

## Description

Assigns a pair.

## Syntax

```cpp
optimized_pair& operator=(const optimized_pair& _Other) noexcept(<expr>);
optimized_pair& operator=(optimized_pair&& _Other) noexcept(<expr>);
```

## Parameters

- `_Other`: The pair to assign from.

## Return value

Returns a reference to the pair that `_Other` was assigned to.

## Exceptions

May throw a specific exception during assignment.

## Remarks

The assignment operator copies/moves the values of `_Other`'s members to the current pair. The operators are marked as **noexcept** if 
the following expressions evaluate to true:

- ```cpp
  std::is_nothrow_copy_assignable_v<_Ty1> && std::is_nothrow_copy_assignable_v<_Ty2>
  ```
- ```cpp
  std::is_nothrow_move_assignable_v<_Ty1> && std::is_nothrow_move_assignable_v<_Ty2>
  ```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)