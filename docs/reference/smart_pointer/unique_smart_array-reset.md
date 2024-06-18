# `unique_smart_array::reset`

## Description

Assigns a new array.

## Syntax

```cpp
void reset(pointer _New_ptr, const size_t _New_size) noexcept;
void reset(nullptr_t = nullptr) noexcept;
```

## Parameters

- `_New_ptr`: The array to assign.
- `_New_size`: The size of the array.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function assigns a new array. If the old array is not null, [delete_object_array](../object_allocator/delete_object_array.md) is called 
before assigning the new array.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)