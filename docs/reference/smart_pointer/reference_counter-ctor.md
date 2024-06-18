# `reference_counter::(constructor)`

## Description

Creates a new `reference_counter` object.

## Syntax

```cpp
reference_counter() noexcept;
explicit reference_counter(const long _Refs) noexcept;
```

## Parameters

- `_Refs`: The initial number of references.

## Return value

(none)

## Exceptions

(none)

## Remarks

The constructor initializes the counter to either zero (default constructor) or a user-defined number (explicit constructor).

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [reference_counter](reference_counter.md)