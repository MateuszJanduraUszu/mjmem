# `object_allocator::max_size`

## Description

Retrieves the maximum supported allocation size.

## Syntax

```cpp
size_type max_size() const noexcept;
```

## Parameters

(none)

## Return value

Returns the maximum supported allocation size.

## Exceptions

(none)

## Remarks

The allocator effectively calls the global allocator's `max_size`. However, since the global allocator's return value is in bytes, the value is 
adjusted by dividing it by the size of the selected type. The call is equivalent to:

```cpp
get_allocator().max_size() / sizeof(_Ty);
```

## Requirements

| Requirement             | Value                    |
|-------------------------|--------------------------|
| Include header          | `<object_allocator.hpp>` |
| Minimum library version | `1.0.0`                  |
| Maximum library version | `N/A`                    |

## See also

- [object_allocator](object_allocator.md)