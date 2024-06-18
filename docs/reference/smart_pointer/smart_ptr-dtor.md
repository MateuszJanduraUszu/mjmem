# `smart_ptr::(destructor)`

## Description

Destroys a `smart_ptr` object.

## Syntax

```cpp
~smart_ptr() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The destructor deletes the stored pointer if it is unique. If the pointer is not null, [delete_object](../object_allocator/delete_object.md) is 
called to release the associated memory. If the stored pointer is null, no action is performed.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)