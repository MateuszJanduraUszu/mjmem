# `unique_smart_ptr::(destructor)`

## Description

Destroys a `unique_smart_ptr` object.

## Syntax

```cpp
~unique_smart_ptr() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The destructor deletes the stored pointer. If the stored pointer is not null, [delete_object](../object_allocator/delete_object.md) is called to 
release the associated memory. If the stored pointer is null, no action is performed.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)