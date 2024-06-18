# `pool_resource::(destructor)`

## Description

Destroys a `pool_resource` object.

## Syntax

```cpp
~pool_resource() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The destructor deallocates the associated memory block, if any is allocated; otherwise, it performs no actions.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<pool_resource.hpp>` |
| Minimum library version | `1.0.0`               |
| Maximum library version | `N/A`                 |

## See also

- [pool_resource](pool_resource.md)