# `reference_counter::unique`

## Description

Checks if the resource is unique based on the counter.

## Syntax

```cpp
bool unique() const noexcept;
```

## Parameters

(none)

## Return value

Returns true if the counter indicates resource uniqueness; otherwise, returns false.

## Exceptions

(none)

## Remarks

The function atomically loads the number of references, ensuring thread-safety, then checks if the value is one. The call is equivalent to:

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

- [reference_counter](reference_counter.md)