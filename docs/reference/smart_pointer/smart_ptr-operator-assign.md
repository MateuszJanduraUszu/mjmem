# `smart_ptr::operator=`

## Description

Assigns a smart pointer.

## Syntax

```cpp
smart_ptr& operator=(const smart_ptr& _Other) noexcept;
smart_ptr& operator=(smart_ptr&& _Other) noexcept;
smart_ptr& operator=(unique_smart_ptr<_Ty>&& _Sptr);
```

## Parameters

- `_Other`: The smart pointer to assign.
- `_Sptr`: The unique smart pointer to assign.

## Return value

Returns a refernce to the `smart_ptr` instance that `_Other` or `_Sptr` was assigned to.

## Exceptions

- (none)
- (none)
- May throw a specific exception if the reference counter creation fails.

## Remarks

The assignment operators assign a smart pointer or a unique smart pointer. The copy assignment operator assigns the pointer stored by 
`_Other` and increments the reference counter. The move assignment operator transfers both the stored pointer and the reference 
counter from `_Other`. The `unique_smart_ptr` assignment operator assigns the pointer stored by `_Sptr` and constructs a new reference 
counter, the pointer is retrieved by calling `_Sptr.release()`.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)