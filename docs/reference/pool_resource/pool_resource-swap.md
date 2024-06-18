# `pool_resource::swap`

## Description

Swaps two resources.

## Syntax

```cpp
void swap(pool_resource& _Other) noexcept;
```

## Parameters

- `_Other`: A reference to the resource to swap with.

## Return value

(none)

## Exceptions

(none)

## Remarks

The function swaps two resources, resulting in the left-side resource owning the right-side's resource and vice versa. Both the data and 
the size are swapped.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<pool_resource.hpp>` |
| Minimum library version | `1.0.0`               |
| Maximum library version | `N/A`                 |

## See also

- [pool_resource](pool_resource.md)