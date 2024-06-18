# `smart_array::reset`

## Description

Assigns a new array.

## Syntax

```cpp
void reset() noexcept;
void reset(pointer _New_ptr, const size_t _New_size);
```

## Parameters

- `_New_ptr`: The array to assign.
- `_New_size`: The size of the array.

## Return value

(none)

## Exceptions

- (none)
- May throw a specific exception if the resource counter creation fails.

## Remarks

The function releases the old array. If the array is unique, [delete_object_array](../object_allocator/delete_object_array.md) is called to 
delete it and the reference counter. If a new array is assigned, a new reference counter is created.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)