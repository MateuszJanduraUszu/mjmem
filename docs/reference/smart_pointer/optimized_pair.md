# `optimized_pair`

## Description

Defines an optimization class that utilizes Empty Base Class Optimization (EBCO) if possible. 

## Syntax

```cpp
template <class _Ty1, class _Ty2>
class optimized_pair {
public:
    using first_type  = _Ty1;
    using second_type = _Ty2;

    optimized_pair() noexcept(<expr>);
    optimized_pair(const _Ty1& _Val1, const _Ty2& _Val2) noexcept(<expr>);
    optimized_pair(_Ty1&& _Val1, _Ty2&& _Val2) noexcept(<expr>);

    optimized_pair(const optimized_pair&) = default; 
    optimized_pair(optimized_pair&&)      = default;
    ~optimized_pair() noexcept            = default;

    optimized_pair& operator=(const optimized_pair& _Other) noexcept(<expr>);
    optimized_pair& operator=(optimized_pair&& _Other) noexcept(<expr>);

    first_type& first() noexcept;
    const first_type& first() const noexcept;
    second_type& second() noexcept;
    const second_type& second() const noexcept;
    void swap(optimized_pair& _Other) noexcept;
};
```

## Member types

| Type        | Definition |
|-------------|------------|
| first_type  | _Ty1       |
| second_type | _Ty2       |

## Member functions

- [(constructor)](optimized_pair-ctor.md)
- [(destructor)](optimized_pair-dtor.md)
- [operator=](optimized_pair-operator-assign.md)
- [first](optimized_pair-first.md)
- [second](optimized_pair-second.md)
- [swap](optimized_pair-swap.md)

## Member constants

(none)

## Non-member functions

- [operator==](optimized_pair-operator-cmp.md)
- [make_optimized_pair](make_optimized_pair.md)

## Remarks

The `optimized_pair` class aims to optimize memory usage by leveraging the Empty Base Class Optimization (EBCO) when possible. 
This can lead to more efficient memory layout and usage, especially when one or both types are empty classes. If the optimization is 
possible, `_Ty1` is stored, and `_Ty2` is derived. Otherwise, both are stored inside the class.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [make_optimized_pair](make_optimized_pair.md)
- [reference_counter](reference_counter.md)