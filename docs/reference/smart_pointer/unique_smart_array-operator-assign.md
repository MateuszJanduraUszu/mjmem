# `unique_smart_array::operator=`

## Description

Assigns a smart pointer.

## Syntax

```cpp
unique_smart_array& operator=(unique_smart_array&& _Other) noexcept;
unique_smart_array& operator=(nullptr_t) noexcept;
```

## Parameters

- `_Other`: The smart pointer to assign.

## Return value

Returns a reference to the object that `_Other` was assigned to.

## Exceptions

(none)

## Remarks

The assignment operators assign a user-provided array or null pointer. If a null pointer is assigned, the stored array is destroyed by 
calling [reset](unique_smart_array-reset.md).

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)