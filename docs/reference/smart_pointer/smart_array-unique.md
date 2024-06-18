# `smart_array::unique`

## Description

Checks if the stored array is unique.

## Syntax

```cpp
bool unique() const noexcept;
```

## Parameters

(none)

## Return value

Returns true if the stored array is unique; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function returns true if the stored array is unique. Uniqueness means that only one `smart_array` instance stores that array. 
It is equivalent to:

```cpp
use_count() == 1;
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)