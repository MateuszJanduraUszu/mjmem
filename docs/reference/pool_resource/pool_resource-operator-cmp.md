# `operator==` (`pool_resource`)

## Description

Compares two resources for equality.

## Syntax

```cpp
bool operator==(const pool_resource& _Left, const pool_resource& _Right);
```

## Parameters

- `_Left`: A left-side resource to compare.
- `_Right`: A right-side resource to compare.

## Return value

Returns true if the two resources are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

Two `pool_resource` objects are considered equal if they manage the same memory block of the same size. This behavior is equivalent to
`_Left.data() == _Right.data() && _Left.size() == _Right.size()`.

## Requirements

| Requirement     | Value                 |
|-----------------|-----------------------|
| Include header  | `<pool_resource.hpp>` |
| Library version | `1.0.0` or newer      |

## See also

- [pool_resource](pool_resource.md)