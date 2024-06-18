# `synchronized_allocator::(destructor)`

## Description

Destroys a `synchronized_allocator` object.

## Syntax

```cpp
~synchronized_allocator() noexcept override;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

Since the `synchronized_allocator` is merely a wrapper around another allocator to provide thread-safety, it does not need to perform 
any specific cleanup actions upon destruction.

## Requirements

| Requirement             | Value                          |
|-------------------------|--------------------------------|
| Include header          | `<synchronized_allocator.hpp>` |
| Minimum library version | `1.0.0`                        |
| Maximum library version | `N/A`                          |

## See also

- [synchronized_allocator](synchronized_allocator.md)