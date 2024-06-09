# `synchronized_allocator::(constructor)`

## Description

Creates a new `synchronized_allocator` object.

## Syntax

```cpp
explicit synchronized_allocator(allocator& _Al) noexcept;
```

## Parameters

- `_Al`: A reference to the allocator to associate with.

## Return value

(none)

## Exceptions

(none)

## Remarks

The constructor takes a reference to the allocator that will be protected by the lock. From this point on, each call to the 
`synchronized_allocator` will invoke the corresponding function of the associated allocator, ensuring that the allocator is protected 
against concurrent access by multiple threads.

## Requirements

| Requirement             | Value                          |
|-------------------------|--------------------------------|
| Include header          | `<synchronized_allocator.hpp>` |
| Minimum library version | `1.0.0`                        |
| Maximum library version | `N/A`                          |

## See also

- [synchronized_allocator](synchronized_allocator.md)