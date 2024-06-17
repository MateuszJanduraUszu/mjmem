# `unique_smart_ptr::release`

## Description

Exchanges the stored pointer with a null pointer.

## Syntax

```cpp
pointer release() noexcept;
```

## Parameters

(none)

## Return value

Returns the stored pointer.

## Exceptions

(none)

## Remarks

The function exchanges the stored pointer with a null pointer and returns the old pointer. Note that if you do not assign the returned 
pointer to any variable, it will be impossible to recover it.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)