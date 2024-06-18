# `smart_array::operator=`

## Description

Assigns a smart pointer.

## Syntax

```cpp
smart_array& operator=(const smart_array& _Other) noexcept;
smart_array& operator=(smart_array&& _Other) noexcept;
smart_array& operator=(unique_smart_array<_Ty>&& _Sarr);
```

## Parameters

- `_Other`: The smart pointer to assign.
- `_Sarr`: The unique smart pointer to assign.

## Return value

Returns a reference to the object that `_Other` was assigned to.

## Exceptions

- (none)
- (none)
- May throw a specific exception if the reference counter creation fails.

## Remarks

The assignment operators assign a smart pointer or a unique smart pointer. The copy assignment operator assigns the array stored by 
`_Other` and increments the reference counter. The move assignment operator transfers both the stored array and the reference counter 
from `_Other`. The `unique_smart_array` assignment operator assigns the array stored by `_Sarr` and constructs a new reference counter, 
the array is retrieved by calling `_Sarr.release()`.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)