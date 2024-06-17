# `optimized_pair::first`

## Description

Retrieves the first element from the pair.

## Syntax

```cpp
first_type& first() noexcept;
const first_type& first() const noexcept;
```

## Parameters

(none)

## Return value

Returns a read-write or read-only reference to the first element.

## Exceptions

(none)

## Remarks

The function provides two variants: read-write and read-only. The first variant is useful when the value needs to be modified, while the 
second variant is intended for read-only access. 

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)