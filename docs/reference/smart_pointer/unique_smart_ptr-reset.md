# `unique_smart_ptr::reset`

## Description

Assigns a new pointer.

## Syntax

```cpp
void reset(pointer _New_ptr = nullptr) noexcept;
```

## Parameters

- `_New_ptr`: The pointer to assign.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function assigns a new pointer. If the old pointer is not null, [delete_object](../object_allocator/delete_object.md) is called before 
assigning the new pointer.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)