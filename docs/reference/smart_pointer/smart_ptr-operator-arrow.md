# `smart_ptr::operator->`

## Description

Retrieves the stored pointer.

## Syntax

```cpp
pointer operator->() const noexcept;
```

## Parameters

(none)

## Return value

Returns the stored pointer.

## Exceptions

(none)

## Remarks

The function returns the stored pointer to access the object that the pointer points to. The call is equivalent to:

```cpp
get()-><member>;
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)