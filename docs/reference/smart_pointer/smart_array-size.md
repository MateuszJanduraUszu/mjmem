# `smart_array::size`

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
| Minimum library version | `2.0.0`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)