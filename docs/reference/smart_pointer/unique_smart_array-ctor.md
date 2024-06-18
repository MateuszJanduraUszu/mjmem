# `unique_smart_array::(constructor)`

## Description

Creates a new `unique_smart_array` object.

## Syntax

```cpp
unique_smart_array() noexcept;
unique_smart_array(unique_smart_array&& _Other) noexcept;
unique_smart_array(nullptr_t) noexcept;
unique_smart_array(pointer _Ptr, const size_t _Size) noexcept;
```

## Parameters

- `_Other`: The smart pointer to move construct with.
- `_Ptr`: The array to assign.
- `_Size`: The size of the array.

## Return value

(none)

## Exceptions

(none)

## Remarks

The constructors assign a default or user-provided array. The `nullptr_t` constructor initializes the smart pointer to store a null pointer, 
which is equivalent to the behavior of the default constructor.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)