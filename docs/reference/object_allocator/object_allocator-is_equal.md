# `object_allocator::is_equal`

## Description

Compares two allocators for equality.

## Syntax

```cpp
bool is_equal(const object_allocator& _Other) const noexcept;
```

## Parameters

- `_Other`: The allocator to compare with.

## Return value

Returns true if the two allocators are equal; otherwise, returns false.

## Exceptions

(none)

## Remarks

Since the allocator is stateless, the result of this call is always true.

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)