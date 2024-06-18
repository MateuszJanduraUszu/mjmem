# `smart_ptr::operator*`

## Description

Dereferences the stored pointer.

## Syntax

```cpp
element_type& operator*() const noexcept;
```

## Parameters

(none)

## Return value

Returns a reference to the object that the pointer points to.

## Exceptions

(none)

## Remarks

The function dereferences the stored pointer. The behavior is undefined if the stored pointer is null. It is equivalent to:

```cpp
*get();
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)