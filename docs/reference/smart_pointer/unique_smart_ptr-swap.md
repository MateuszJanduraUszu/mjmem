# `unique_smart_ptr::swap`

## Description

Swaps two smart pointers.

## Syntax

```cpp
void swap(unique_smart_ptr& _Other) noexcept;
```

## Parameters

- `_Other`: The smart pointer to swap with.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function swaps the stored pointers between the two `unique_smart_ptr` instances.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)