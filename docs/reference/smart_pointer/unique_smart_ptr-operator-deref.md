# `unique_smart_ptr::operator*`

## Description

Dereferences the stored pointer.

## Syntax

```cpp
element_type& operator*() const noexcept(<expr>);
```

## Parameters

(none)

## Return value

Returns a reference to the object that the pointer points to.

## Exceptions

May throw a specific exception if the dereference fails.

## Remarks

The function dereferences the stored pointer. The behavior is undefined if the stored pointer is null. The operator is marked as 
**noexcept** if the following expression evaluates to true:

```cpp
noexcept(*std::declval<pointer>())
```

The function is equivalent to:

```cpp
*get();
```

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)