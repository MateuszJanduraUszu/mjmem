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