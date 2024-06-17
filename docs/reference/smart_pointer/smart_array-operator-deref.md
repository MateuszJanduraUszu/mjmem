# `smart_array::operator*`

## Description

Retrieves the first element of the stored array.

## Syntax

```cpp
element_type& operator*() const noexcept;
```

## Parameters

(none)

## Return value

Returns a read-only reference to the first element of the stored array.

## Exceptions

(none)

## Remarks

The function returns the first element of the stored array. The behavior is undefined if the stored array is null. It is equivalent to:

```cpp
*get();
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)