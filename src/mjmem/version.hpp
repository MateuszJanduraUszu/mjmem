// version.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_VERSION_HPP_
#define _MJMEM_VERSION_HPP_
#include <cstdint>

// Note: Encodes a version number from major, minor, and patch components into a 64-bit integer.
//       The major version consumes 16 bits, while the minor and patch each consume 24 bits.
#define _MJX_ENCODE_VERSION(_Major, _Minor, _Patch) ((static_cast<uint64_t>(_Major) << 48ULL)  \
                                                    | (static_cast<uint64_t>(_Minor) << 24ULL) \
                                                    | static_cast<uint64_t>(_Patch))

// decodes the major, minor, and patch version numbers from a 64-bit encoded version
#define _MJX_DECODE_VERSION_MAJOR(_Version) ((static_cast<uint64_t>(_Version) & 0xFFFF'0000'0000'0000ULL) >> 48ULL)
#define _MJX_DECODE_VERSION_MINOR(_Version) ((static_cast<uint64_t>(_Version) & 0x0000'FFFF'FF00'0000ULL) >> 24ULL)
#define _MJX_DECODE_VERSION_PATCH(_Version) ((static_cast<uint64_t>(_Version) & 0x0000'0000'00FF'FFFFULL)

// defines the latest MJMEM library version, synchronized with the version specified in 'res/mjmem.rc'
#define _MJMEM_VERSION_MAJOR 2
#define _MJMEM_VERSION_MINOR 0
#define _MJMEM_VERSION_PATCH 0
#define _MJMEM_VERSION       _MJX_ENCODE_VERSION(_MJMEM_VERSION_MAJOR, _MJMEM_VERSION_MINOR, _MJMEM_VERSION_PATCH)

// checks whether the current version is greater than or equal to the specified version
#define _MJMEM_VERSION_SUPPORTED(_Major, _Minor, _Patch) \
    (_MJMEM_VERSION >= _MJX_ENCODE_VERSION(_Major, _Minor, _Patch))
#endif // _MJMEM_VERSION_HPP_