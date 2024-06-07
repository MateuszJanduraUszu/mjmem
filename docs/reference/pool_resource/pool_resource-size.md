# `pool_resource::size`

## Description

Retrieves the size of the stored resource.

## Syntax

```cpp
size_type size() const noexcept;
```

## Parameters

(none)

## Return value

Returns the size of the stored resource.

## Exceptions

(none)

## Remarks

The function returns the size of the stored resource. If the resource is empty, the returned size is zero.

## Requirements

| Requirement     | Value                 |
|-----------------|-----------------------|
| Include header  | `<pool_resource.hpp>` |
| Library version | `1.0.0` or newer      |

## See also

- [pool_resource](pool_resource.md)