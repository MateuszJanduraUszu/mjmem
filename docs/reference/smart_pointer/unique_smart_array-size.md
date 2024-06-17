# `unique_smart_array::size`

## Description

Retrieves the size of the stored array.

## Syntax

```cpp
size_t size() const noexcept;
```

## Parameters

(none)

## Return value

Returns the size of the stored array.

## Exceptions

(none)

## Remarks

The function returns the size of the stored array. If the stored array is null, the result of this call is zero.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)