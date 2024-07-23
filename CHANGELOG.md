# MJMEM Changelog

All notable changes to this project will be documented in this file.

## `1.0.0` (2023-12-20)

### **Added**

* Initial release

## `1.0.1` (2023-12-26)

### **Added**

* Introduced smart pointers

### **Changed**

* Made `object_allocator<T>` compatible with standard allocators
* Replaced `pool_exhausted` exception with `allocation_failure`

### **Removed**

* Removed `pool_exhausted` class (replaced by `allocation_failure`)

## `1.0.2` (2024-02-12)

### **Added**

* Introduced allocator-aware object management
* Upgraded C++ standard version to C++20

## `2.0.0` (2024-07-23)

### **Added**

* Added comprehensive documentation
* Added this changelog
* Added `mjmem.rc` resource file
* Added benchmarks to measure performance improvements
* Integrated CMake as the build system
* Integrated GitHub Workflows for CI/CD
* Implemented code-level versioning
* Implemented `block_allocator::block_size()` and `block_allocator::resource()`
* Implemented `pool_allocator::resource()`
* Implemented missing `smart_array::size()`
* Implemented allocation tracking for `pool_resource`-based allocators in debug mode

### **Changed**

* Optimized the internal list of free blocks in `pool_allocator`
* Optimized the internal bitmap in `block_allocator`
* Reduced the number of `dynamic_allocator` objects to improve performance
* Ported old tests to the new build system

### **Removed**

* Removed `operator*()` and `operator->()` from `unique_smart_array` and `smart_array`
* Removed `pool_allocator::free_blocks()`

### **Fixed**

* Fixed the default constructor for `reference_counter`
* Fixed `is_equal()` for stateless allocators
* Corrected `noexcept` usage for several functions