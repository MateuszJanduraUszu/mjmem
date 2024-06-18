# `reference_counter::(destructor)`

## Description

Destroys a `reference_counter` object.

## Syntax

```cpp
~reference_counter() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

Even though the constructor stores the number of references, the destructor is trivial, meaning it does not perform any specific actions.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [reference_counter](reference_counter.md)