# `operator==` (`pool_resource`)

## Description

Compares two resources for equality.

## Syntax

```cpp
bool operator==(const pool_resource& _Left, const pool_resource& _Right);
```

## Parameters

- `_Left`: The left-side resource to compare.
- `_Right`: The right-side resource to compare.

## Return value

Returns true if the two resources are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

Two `pool_resource` objects are considered equal if they manage the same memory block of the same size. The function is equivalent to:

```cpp
_Left.data() == _Right.data() && _Left.size() == _Right.size();
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<pool_resource.hpp>` |
| Minimum library version | `1.0.0`               |
| Maximum library version | `N/A`                 |

## See also

- [pool_resource](pool_resource.md)