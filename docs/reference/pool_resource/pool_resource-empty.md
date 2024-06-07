# `pool_resource::empty`

## Description

Checks if the resource is empty.

## Syntax

```cpp
bool empty() const noexcept;
```

## Parameters

(none)

## Return value

Returns true if the resource is empty; otherwise, returns false.

## Exceptions

(none)

## Remarks

The resource is considered empty when it does not own any memory block or its size is zero. To destroy the resource, call [destroy()](pool_resource-destroy.md).

## Requirements

| Requirement     | Value                 |
|-----------------|-----------------------|
| Include header  | `<pool_resource.hpp>` |
| Library version | `1.0.0` or newer      |

## See also

- [pool_resource](pool_resource.md)