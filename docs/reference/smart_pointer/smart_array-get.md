# `smart_array::get`

## Description

Retrieves the stored array.

## Syntax

```cpp
pointer get() const noexcept;
```

## Parameters

(none)

## Return value

Returns the stored array.

## Exceptions

(none)

## Remarks

The function returns the stored array. If the class does not store any array, the result of this call is a null pointer.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)