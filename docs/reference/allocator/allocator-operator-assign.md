# `allocator::operator=`

## Description

Assigns an allocator.

## Syntax

```cpp
allocator& operator=(const allocator& _Other) noexcept;
allocator& operator=(allocator&& _Other) noexcept;
```

## Parameters

* `_Other`: The allocator to assign from.

## Return value

Returns a reference to the allocator that `_Other` was assigned to.

## Exceptions

(none)

## Remarks

Although the function itself has no visible effect, it is defined to allow its usage in a derived class.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<allocator.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocator](allocator.md)