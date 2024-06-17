# `smart_ptr::swap`

## Description

Swaps two smart pointers.

## Syntax

```cpp
void swap(smart_ptr& _Other) noexcept;
```

## Parameters

- `_Other`: The smart pointer to swap with.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function swaps the stored pointers and reference counters between the two `smart_ptr` instances.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)