# `unique_smart_ptr::(constructor)`

## Description

Creates a new `unique_smart_ptr` object.

## Syntax

```cpp
unique_smart_ptr() noexcept;
unique_smart_ptr(unique_smart_ptr&& _Other) noexcept;
unique_smart_ptr(nullptr_t) noexcept;
explicit unique_smart_ptr(pointer _Ptr) noexcept;
```

## Parameters

- `_Other`: The smart pointer to move construct with.
- `_Ptr`: The pointer to store.

## Return value

(none)

## Exceptions

(none)

## Remarks

The constructors assign a default or user-provided pointer. The `nullptr_t` constructor initializes the smart pointer to store a null pointer, which is equivalent to the behavior of the default constructor.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)