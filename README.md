# MJMEM

MJMEM is an internal module designed for use in future projects. It is written in C++17.

## Setup

1. Download the appropriate package based on your system architecture:

    * For 64-bit systems, download `Bin-x64.zip`.
    * For 32-bit systems, download `Bin-x86.zip`.

2. Extract the downloaded package. You should see the following directories:

    * `bin` - Debug and release binaries.
    * `inc` - Include headers.

3. Include the `inc\mjmem` directory in your project as an additional include directory.
4. Link `bin\{Debug|Release}\mjmem.lib` library to your project.
5. Don't forget to include the `bin\{Debug|Release}\mjmem.dll` in your project's
output directory if your application relies on it during runtime.

## Usage

To integrate MJMEM into your project, you can include the appropriate header files
based on your requirements:

* **<mjmem/allocator.hpp>**: `allocator` abstract class and global allocator.
* **<mjmem/api.hpp>**: Export/import macro, don't include it directly.
* **<mjmem/block_allocator.hpp>**: Fixed-size block allocator.
* **<mjmem/dynamic_allocator.hpp>**: Allocator that wraps `new`/`delete`.
* **<mjmem/exception.hpp>**: Memory exception classes.
* **<mjmem/object_allocator.hpp>**: Type-specific wrapper around global allocator.
* **<mjmem/pool_allocator.hpp>**: Variable-size block allocator.
* **<mjmem/pool_resource.hpp>**: Memory block that serves as a pool resource.
* **<mjmem/synchronized_allocator.hpp>**: Thread-safe wrapper around the specified allocator.

## Compatibility

MJMEM is compatible with all versions of Windows.
Additionally, the project requires support for C++17.

## Questions and support

If you have any questions, encouter issues, or need assistance with the MJSTR,
feel free to reach out. You can reach me through the `Issues` section or email
([mjandura03@gmail.com](mailto:mjandura03@gmail.com)).

## License

Copyright © Mateusz Jandura.

SPDX-License-Identifier: Apache-2.0