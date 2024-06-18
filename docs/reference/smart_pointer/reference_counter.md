# `reference_counter`

## Description

Defines an atomic reference counter.

## Syntax

```cpp
class reference_counter {
public:
    reference_counter() noexcept;
    ~reference_counter() noexcept;

    explicit reference_counter(const long _Refs) noexcept;

    reference_counter(const reference_counter&)            = delete;
    reference_counter& operator=(const reference_counter&) = delete;

    void increment() noexcept;
    long decrement() noexcept;
    long use_count() const noexcept;
    bool unique() const noexcept;
};
```

## Member types

(none)

## Member functions

- [(constructor)](reference_counter-ctor.md)
- [(destructor)](reference_counter-dtor.md)
- [increment](reference_counter-increment.md)
- [decrement](reference_counter-decrement.md)
- [use_count](reference_counter-use_count.md)
- [unique](reference_counter-unique.md)

## Member constants

(none)

## Non-member functions

(none)

## Remarks

The class is useful for resources that are reference-counted. It uses atomic operations to ensure thread-safety in a multithreading 
environment.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [optimized_pair](optimized_pair.md)
- [smart_array](smart_array.md)
- [smart_ptr](smart_ptr.md)