# MJX Memory Module (MJMEM) [![Status Badge][status-badge-image]][status-badge-link]

The MJMEM library is a memory management toolset designed as a module for future MJX projects.

- [Changelog][] tracks all changes made in each release.
- [License][] defines the legal rights regarding the use of this library.
- [Documentation][] describes all functions and classes included in this library.

# Build steps

Follow these steps to build and install MJMEM on your system:

1. Install the required tools.

    - Download and install [CMake][] 3.21.0 or later.
    - Ensure you have a compatible compiler that supports C++20.

2. Clone the repository.

    - Open a command-line interface.
    - Invoke `git clone https://github.com/MateuszJanduraUszu/mjmem.git --recurse-submodules`.

3. Choose the architecture and configuration.

    - Supported architectures are defined in `CMakePresets.json`. The architecture is automatically selected when specifying a preset.
    - Only `Debug` and `Release` configurations are supported.

4. Build and, optionally, install the project.

    - To build tests, benchmarks, or install the library, consider setting the `MJMEM_BUILD_BENCHMARKS`, `MJMEM_BUILD_TESTS`, and `MJMEM_INSTALL_LIBRARY` options, respectively.
    - Invoke `cmake --preset=<preset> [options...]`.
    - Build the project with `cmake --build build/<arch> --preset=<preset> --config <config>`.
    - To install the library, invoke `cmake --install build/<arch> --config <config>`.

# Testing and benchmarking

Before running any benchmarks or tests, ensure the library is successfully built.

To run the tests:

1. Open a command-line interface.
2. Change the current directory to the cloned `mjmem` directory.
3. Invoke `ctest --test-dir build/<arch>/tests --output-on-failure -C <config>`.

To run a benchmark:

1. Open a command-line interface.
2. Change the current directory to the cloned `mjmem` directory.
3. Invoke `build\<arch>\benchmarks\<config>\<benchmark-name>`.

Note that while all tests are invoked by CTest in a single run, benchmarks are standalone programs that must be invoked separately.

# How to consume

To use the library:

1. Include the `mjmem` header files directory.
2. Link the `mjmem.lib` static library.
3. Copy the `mjmem.dll` dynamic library to the directory where the executable that uses MJMEM is located.

To integrate into another project:

1. Add `mjmem` as a submodule.

    - Open a command-line interface.
    - Invoke `git submodule add mjmem https://github.com/MateuszJanduraUszu/mjmem.git <path>`.

2. In your CMake script, add `mjmem` as an external target.

    - In your top-level `CMakeLists.txt`, add `add_subdirectory(<path-to-mjmem>)`.

3. Include the `mjmem` header files directory and link the generated static library.

    - Include the header files directory with `target_include_directories(<target> <scope> "<path-to-mjmem>/src")`.
    - Link the static library with `target_link_libraries(<target> <scope> mjmem)`.

4. Copy the `mjmem.dll` dynamic library to your project's output directory.

    ```cmake
    add_custom_command(TARGET <target> POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:mjmem>"
        "$<TARGET_FILE_DIR:<target>>"
    )
    ```

Replace the placeholders with the appropriate values for your project.

# Compatibility

The MJMEM library is designed to work with Windows 10 and above. While it is optimized for these versions, it may also be 
compatible with older Windows versions. However, official support is focused on Windows 10 and newer versions.

# Questions and support

If you have any questions, encounter issues, or need assistance with the MJMEM, feel free to reach out. You can contact me through 
the [issues][] section or via [email][].

# License

Copyright © Mateusz Jandura.

SPDX-License-Identifier: Apache-2.0

[status-badge-image]: https://github.com/MateuszJanduraUszu/mjmem/actions/workflows/build-and-test.yml/badge.svg
[status-badge-link]: https://github.com/MateuszJanduraUszu/mjmem/actions/workflows/build-and-test.yml
[Changelog]: CHANGELOG.md
[License]: LICENSE
[Documentation]: docs/README.md
[CMake]: https://cmake.org/download
[issues]: https://github.com/MateuszJanduraUszu/mjmem/issues
[email]: mailto:mjandura03@gmail.com