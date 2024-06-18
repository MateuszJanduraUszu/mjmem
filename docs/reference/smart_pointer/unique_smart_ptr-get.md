# `unique_smart_ptr::get`

## Description

Retrieves the stored pointer.

## Syntax

```cpp
pointer get() const noexcept;
```

## Parameters

(none)

## Return value

Returns the stored pointer.

## Exceptions

(none)

## Remarks

The function returns the stored pointer. If the class does not store any pointer, the result of this call is a null pointer.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)