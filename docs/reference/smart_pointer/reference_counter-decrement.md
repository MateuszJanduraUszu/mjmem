# `reference_counter::decrement`

## Description

Decrements the number of references.

## Syntax

```cpp
long decrement() noexcept;
```

## Parameters

(none)

## Return value

Returns the new number of references.

## Exceptions

(none)

## Remarks

The function atomically decrements the counter, ensuring thread-safety.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [reference_counter](reference_counter.md)