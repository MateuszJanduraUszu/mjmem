// api.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_API_HPP_
#define _MJMEM_API_HPP_

#ifdef _MJMEM_BUILD
#define _MJMEM_API __declspec(dllexport)
#else // ^^^ _MJMEM_BUILD ^^^ / vvv !_MJMEM_BUILD vvv
#define _MJMEM_API __declspec(dllimport)
#endif // _MJMEM_BUILD
#endif // _MJMEM_API_HPP_