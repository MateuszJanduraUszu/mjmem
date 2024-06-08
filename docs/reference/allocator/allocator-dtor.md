# `allocator::(destructor)`

## Description

Destroys an `allocator` object.

## Syntax

```cpp
virtual ~allocator() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The destructor is marked as `virtual` to ensure that derived class destructors are called correctly during object destruction. The base class 
destructor is trivial, meaning it performs no specific actions.

## Requirements

| Requirement             | Value             |
|-------------------------|-------------------|
| Include header          | `<allocator.hpp>` |
| Minimum library version | `1.0.0`           |
| Maximum library version | `N/A`             |

## See also

- [allocator](allocator.md)