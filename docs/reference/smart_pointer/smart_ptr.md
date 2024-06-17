# `smart_ptr`

## Description

Defines a smart pointer with shared object ownership semantics.

## Syntax

```cpp
template <class _Ty>
class smart_ptr {
public:
    using element_type = _Ty;
    using pointer      = _Ty*;

    smart_ptr() noexcept;
    smart_ptr(const smart_ptr& _Other) noexcept;
    smart_ptr(smart_ptr&& _Other) noexcept;
    ~smart_ptr() noexcept;

    smart_ptr(nullptr_t) noexcept;
    explicit smart_ptr(pointer _Ptr);
    smart_ptr(unique_smart_ptr<_Ty>&& _Sptr);

    smart_ptr& operator=(const smart_ptr& _Other) noexcept;
    smart_ptr& operator=(smart_ptr&& _Other) noexcept;
    smart_ptr& operator=(unique_smart_ptr<_Ty>&& _Sptr);

    explicit operator bool() const noexcept;
    element_type& operator*() const noexcept;
    pointer operator->() const noexcept;
    pointer get() const noexcept;
    long use_count() const noexcept;
    bool unique() const noexcept;
    void reset() noexcept;
    void reset(pointer _New_ptr);
    void swap(smart_ptr& _Other) noexcept;
};
```

## Member types

| Type         | Definition |
|--------------|------------|
| element_type | _Ty        |
| pointer      | _Ty*       |

## Member functions

- [(constructor)](smart_ptr-ctor.md)
- [(destructor)](smart_ptr-dtor.md)
- [operator=](smart_ptr-operator-assign.md)
- [operator bool](smart_ptr-operator-bool.md)
- [operator*](smart_ptr-operator-deref.md)
- [operator->](smart_ptr-operator-arrow.md)
- [get](smart_ptr-get.md)
- [use_count](smart_ptr-use_count.md)
- [unique](smart_ptr-unique.md)
- [reset](smart_ptr-reset.md)
- [swap](smart_ptr-swap.md)

## Member constants

(none)
  
## Non-member functions

- [operator==](smart_ptr-operator-cmp.md)
- [make_smart_ptr](make_smart_ptr.md)

## Remarks

The class is a wraper around a pointer that ensures the pointer is destroyed when the class is destructed and the pointer is unique. 
It shares ownership of the pointer with other instances via reference-counting.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_array](smart_array.md)
- [unique_smart_array](unique_smart_array.md)
- [unique_smart_ptr](unique_smart_ptr.md)