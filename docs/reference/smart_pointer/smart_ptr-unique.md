# `smart_ptr::unique`

## Description

Checks if the stored pointer is unique.

## Syntax

```cpp
bool unique() const noexcept;
```

## Parameters

(none)

## Return value

Returns true if the stored pointer is unique; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function returns true if the stored pointer is unique. Uniqueness means that only one `smart_ptr` instance stores that pointer. 
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

- [smart_ptr](smart_ptr.md)