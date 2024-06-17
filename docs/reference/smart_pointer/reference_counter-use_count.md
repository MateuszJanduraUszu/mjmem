# `reference_counter::use_count`

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

The function atomically loads the number of references, ensuring thread-safety.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [reference_counter](reference_counter.md)