# `unique_smart_ptr::operator=`

## Description

Assigns a smart pointer.

## Syntax

```cpp
unique_smart_ptr& operator=(unique_smart_ptr&& _Other) noexcept;
unique_smart_ptr& operator=(nullptr_t) noexcept;
```

## Parameters

- `_Other`: The smart pointer to assign.

## Return value

Returns a reference to the object that `_Other` or a null pointer was assigned to.

## Exceptions

(none)

## Remarks

The assignment operators assign a user-provided pointer or null pointer. If a null pointer is assigned, the old pointer is destroyed by 
calling [reset](unique_smart_ptr-reset.md).

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)