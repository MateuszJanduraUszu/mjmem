# `smart_array::swap`

## Description

Swaps two smart pointers.

## Syntax

```cpp
void swap(smart_array& _Other) noexcept;
```

## Parameters

- `_Other`: The smart pointer to swap with.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function swaps the stored arrays and reference counters between the two `smart_array` instances.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)