# `pool_resource::destroy`

## Description

Destroys the stored memory block.

## Syntax

```cpp
void destroy() noexcept;
```

## Parameters

(none)

## Return value

(none)

## Exceptions

(none)

## Remarks

The function first deallocates the stored memory block, then sets the resource size to zero. After this, [empty()](pool_resource-empty.md) always returns true.

## Requirements

| Requirement     | Value                 |
|-----------------|-----------------------|
| Include header  | `<pool_resource.hpp>` |
| Library version | `1.0.0` or newer      |

## See also

- [pool_resource](pool_resource.md)