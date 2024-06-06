# `allocator::operator=`

## Description

Assigns an allocator.

## Syntax

```cpp
allocator& operator=(const allocator& _Other) noexcept;
allocator& operator=(allocator&& _Other) noexcept;
```

## Parameters

* `_Other`: An allocator to assign from.

## Return value

Returns a reference to the allocator that was assigned to.

## Exceptions

(none)

## Remarks

Although the function itself has no visible effect, it is defined to allow its usage in a derived class.

## Requirements

| Requirement     | Value             |
|-----------------|-------------------|
| Include header  | `<allocator.hpp>` |
| Library version | `1.0.0` or newer  |

## See also

- [allocator](allocator.md)