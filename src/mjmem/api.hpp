// api.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_API_HPP_
#define _MJMEM_API_HPP_

// Note: The MJMEM module serves as the foundation for other modules. Therefore, macros are placed
//       in the <mjmem/api.hpp> header. This approach enables sharing macros across multiple modules
//       without concerns about missing definitions.
#ifdef _MJX_MSVC
#define _MJX_NOVTABLE __declspec(novtable)
#else // ^^^ _MJX_MSVC ^^^ / vvv !_MJX_MSVC vvv
#define _MJX_NOVTABLE
#endif // _MJX_MSVC

#ifdef _MJX_WINDOWS
// Windows libraries (DLLs) require an additional attribute
#ifdef _MJMEM_BUILD
#define _MJMEM_API __declspec(dllexport)
#else // ^^^ _MJMEM_BUILD ^^^ / vvv !_MJMEM_BUILD vvv
#define _MJMEM_API __declspec(dllimport)
#endif // _MJMEM_BUILD
#else // ^^^ _MJX_WINDOWS ^^^ / vvv _MJX_LINUX vvv
#define _MJMEM_API
#endif // _MJX_WINDOWS
#endif // _MJMEM_API_HPP_