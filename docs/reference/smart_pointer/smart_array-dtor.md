# `smart_array::(destructor)`

## Description

Destroys a `smart_array` object.

## Syntax

```cpp
~smart_array() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The destructor deletes the stored array if it is unique; otherwise, decremets the number of references only. If the array is not null 
[delete_object_array](../object_allocator/delete_object_array.md) is called to release the associated memory. If the stored array is null, no action is performed.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)