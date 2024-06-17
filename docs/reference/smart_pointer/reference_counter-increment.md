# `reference_counter::increment`

## Description

Increments the number of references.

## Syntax

```cpp
void increment() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The function atomically increments the counter, ensuring thread-safety.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [reference_counter](reference_counter.md)