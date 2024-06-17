# `unique_smart_array::(destructor)`

## Description

Destroys a `unique_smart_array` object.

## Syntax

```cpp
~unique_smart_array() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The destructor deletes the stored array. If the stored array is not null, [delete_object_array](../object_allocator/delete_object_array.md) is 
called to release the associated memory. If the stored array is null, no action is performed.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)