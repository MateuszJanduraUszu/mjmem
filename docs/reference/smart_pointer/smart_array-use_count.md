# `smart_array::use_count`

## Description

Retrieves the number of references.

## Syntax

```cpp
long use_count() const noexcept;
```

## Parameters

(none)

## Return value

Returns the number of references.

## Exceptions

(none)

## Remarks

The function returns the number of references to the stored array. If the stored array is null, zero is returned; otherwise, the number of 
instances that store the stored array is returned.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)