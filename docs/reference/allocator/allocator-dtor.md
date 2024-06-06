# `allocator::(destructor)`

## Description

Destroys the allocator.

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

The destructor is marked as `virtual` to ensure that derived class destructors are called correctly during object destruction. The base class destructor is trivial, meaning it performs no specific actions.

## Requirements

| Requirement     | Value             |
|-----------------|-------------------|
| Include header  | `<allocator.hpp>` |
| Library version | `1.0.0` or newer  |

## See also

- [allocator](allocator.md)