# `pool_resource::release`

## Description

Releases the stored memory block.

## Syntax

```cpp
pointer release() noexcept;
```

## Parameters

(none)

## Return value

Returns a pointer to the released resource. If the resource is empty, the returned value is a null pointer.

## Exceptions

(none)

## Remarks

The function releases the stored memory block and sets the resource size to zero. Before calling this function, ensure that you have 
retrieved the resource size using [size](pool_resource-size.md).

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<pool_resource.hpp>` |
| Minimum library version | `1.0.0`               |
| Maximum library version | `N/A`                 |

## See also

- [pool_resource](pool_resource.md)