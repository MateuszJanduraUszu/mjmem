# `smart_ptr::operator bool`

## Description

Checks if the stored pointer is not null.

## Syntax

```cpp
explicit operator bool() const noexcept;
```

## Parameters

(none)

## Return value

Returns true if the stored pointer is not null; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function checks if the stored pointer is not null. It is equivalent to:

```cpp
get() != nullptr;
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)