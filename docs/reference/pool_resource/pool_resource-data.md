# `pool_resource::data`

## Description

Retrieves the stored memory block.

## Syntax

```cpp
pointer data() noexcept;
const_pointer data() const noexcept;
```

## Parameters

(none)

## Return value

- Returns a read-write pointer to the memory block if the resource is not empty; otherwise, returns a null pointer.
- Returns a read-only pointer to the memory block if the resource is not empty; otherwise, returns a null pointer.

## Exceptions

(none)

## Remarks

The function retrieves a pointer to the managed resource. If the resource is empty, it returns a null pointer. It offers read-write and read-only variants to enable usage of the resource in both mutable and constant contexts.

## Requirements

| Requirement     | Value                 |
|-----------------|-----------------------|
| Include header  | `<pool_resource.hpp>` |
| Library version | `1.0.0` or newer      |

## See also

- [pool_resource](pool_resource.md)