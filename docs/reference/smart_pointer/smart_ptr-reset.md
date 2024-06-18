# `smart_ptr::reset`

## Description

Assigns a new pointer.

## Syntax

```cpp
void reset() noexcept;
void reset(pointer _New_ptr);
```

## Parameters

- `_New_ptr`: The pointer to assign.

## Return value

(none)

## Exceptions

- (none)
- May throw a specific exception if the resource counter creation fails.

## Remarks

The function releases the old pointer. If the pointer is unique, [delete_object](../object_allocator/delete_object.md) is called to delete it and the reference counter. If a new pointer is assigned, a new reference counter is created.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)