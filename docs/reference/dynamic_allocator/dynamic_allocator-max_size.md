# `dynamic_allocator::max_size`

## Description

Retrieves the maximum supported allocation size.

## Syntax

```cpp
size_type max_size() const noexcept override;
```

## Parameters

(none)

## Return value

Returns the maximum supported allocation size.

## Exceptions

(none)

## Remarks

The maximum supported allocation size is the largest value that can be represented by `size_type`. It is equivalent to:

```cpp
static_cast<size_type>(-1);
```

or

```cpp
std::numeric_limits<size_type>::max();
```

## Requirements

| Requirement             | Value                     |
|-------------------------|---------------------------|
| Include header          | `<dynamic_allocator.hpp>` |
| Minimum library version | `1.0.0`                   |
| Maximum library version | `N/A`                     |

## See also

- [dynamic_allocator](dynamic_allocator.md)