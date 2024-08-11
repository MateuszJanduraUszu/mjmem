// rwlock.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_RWLOCK_HPP_
#define _MJMEM_IMPL_RWLOCK_HPP_
#include <mjmem/impl/utils.hpp>
#ifdef _MJX_WINDOWS
#include <mjmem/impl/tinywin.hpp>
#else // ^^^ _MJX_WINDOWS ^^^ / vvv _MJX_LINUX vvv
#include <pthread.h>
#endif // _MJX_WINDOWS

namespace mjx {
    namespace mjmem_impl {
        class _Rw_lock { // reader-writer lock
        public:
            _Rw_lock(const _Rw_lock&)            = delete;
            _Rw_lock& operator=(const _Rw_lock&) = delete;

#ifdef _MJX_WINDOWS
            _Rw_lock() noexcept : _Myhandle{0} {}

            ~_Rw_lock() noexcept {}

            void _Acquire_read_lock() noexcept {
                ::AcquireSRWLockShared(&_Myhandle);
            }

            void _Acquire_write_lock() noexcept {
                ::AcquireSRWLockExclusive(&_Myhandle);
            }

            void _Release_read_lock() noexcept {
                ::ReleaseSRWLockShared(&_Myhandle);
            }

            void _Release_write_lock() noexcept {
                _Analysis_assume_lock_acquired_(_Myhandle);
                ::ReleaseSRWLockExclusive(&_Myhandle);
            }
#else // ^^^ _MJX_WINDOWS ^^^ / vvv _MJX_LINUX vvv
            _Rw_lock() noexcept : _Myhandle{0} {
                _INTERNAL_ASSERT(::pthread_rwlock_init(&_Myhandle, nullptr) == 0, "failed to initialize R/W Lock");
            }

            ~_Rw_lock() noexcept {
                _INTERNAL_ASSERT(::pthread_rwlock_destroy(&_Myhandle) == 0, "failed to destroy R/W Lock");
            }

            void _Acquire_read_lock() noexcept {
                _INTERNAL_ASSERT(::pthread_rwlock_rdlock(&_Myhandle) == 0, "failed to acquire read lock");
            }

            void _Acquire_write_lock() noexcept {
                _INTERNAL_ASSERT(::pthread_rwlock_wrlock(&_Myhandle) == 0, "failed to acquire write lock");
            }

            void _Release_read_lock() noexcept {
                _INTERNAL_ASSERT(::pthread_rwlock_unlock(&_Myhandle) == 0, "failed to release read lock");
            }

            void _Release_write_lock() noexcept {
                _INTERNAL_ASSERT(::pthread_rwlock_unlock(&_Myhandle) == 0, "failed to release write lock");
            }
#endif // _MJX_WINDOWS

        private:
#ifdef _MJX_WINDOWS
            SRWLOCK _Myhandle;
#else // ^^^ _MJX_WINDOWS ^^^ / vvv _MJX_LINUX vvv
            pthread_rwlock_t _Myhandle;
#endif // _MJX_WINDOWS
        };

        class _Read_lock_guard { // RAII class for read lock acquisition
        public:
            _Read_lock_guard(_Rw_lock& _Lock) noexcept : _Mylock(_Lock) {
                _Mylock._Acquire_read_lock();
            }

            ~_Read_lock_guard() noexcept {
                _Mylock._Release_read_lock();
            }

        private:
            _Rw_lock& _Mylock;
        };

        class _Write_lock_guard { // RAII class for write lock acquisition
        public:
            _Write_lock_guard(_Rw_lock& _Lock) noexcept : _Mylock(_Lock) {
                _Mylock._Acquire_write_lock();
            }

            ~_Write_lock_guard() noexcept {
                _Mylock._Release_write_lock();
            }

        private:
            _Rw_lock& _Mylock;
        };
    } // namespace mjmem_impl
} // namespace mjx

#endif // _MJMEM_IMPL_RWLOCK_HPP_