// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>
#include <thread>
#include <vector>

namespace mjx {
    TEST(reference_counter, use_count) {
        reference_counter _Ctr0;
        reference_counter _Ctr1(8);
        reference_counter _Ctr2(64);
        EXPECT_EQ(_Ctr0.use_count(), 0);
        EXPECT_EQ(_Ctr1.use_count(), 8);
        EXPECT_EQ(_Ctr2.use_count(), 64);
    }

    TEST(reference_counter, unique) {
        reference_counter _Ctr0;
        reference_counter _Ctr1(1);
        reference_counter _Ctr2(2);
        EXPECT_FALSE(_Ctr0.unique());
        EXPECT_TRUE(_Ctr1.unique());
        EXPECT_FALSE(_Ctr2.unique());

        _Ctr0.increment();
        _Ctr1.decrement();
        _Ctr2.decrement();
        EXPECT_TRUE(_Ctr0.unique());
        EXPECT_FALSE(_Ctr1.unique());
        EXPECT_TRUE(_Ctr2.unique());
    }

    TEST(reference_counter, parallel_increment) {
        // Note: This test validates the thread-safety of the reference_counter class.
        //       Multiple threads increment the counter concurrently until it reaches
        //       the expected use count. The test ensures that the final count is correct,
        //       demonstrating that the reference_counter handles concurrent operations
        //       without data races or inconsistencies.
        constexpr size_t _Expected_use_count = 64;
        const size_t _Thread_count           = (::std::min)(4U, ::std::thread::hardware_concurrency());
        ::std::vector<::std::thread> _Threads;
        reference_counter _Counter;
        ::std::atomic<bool> _Work_started(false);
        for (size_t _Thread = 0; _Thread < _Thread_count; ++_Thread) {
            _Threads.push_back(::std::thread(
                [&] {
                    _Work_started.wait(false, ::std::memory_order_relaxed); // wait until the work is started
                    while (_Counter.use_count() < _Expected_use_count) { // increment the counter if possible
                        _Counter.increment();
                    }
                }
            ));
        }

        _Work_started.store(true);
        _Work_started.notify_all();
        for (::std::thread& _Thread : _Threads) {
            if (_Thread.joinable()) { // join the threads to avoid a std::terminate() call
                _Thread.join();
            }
        }

        EXPECT_EQ(_Counter.use_count(), _Expected_use_count);
    }

    TEST(reference_counter, parallel_decrement) {
        // Note: This test validates the thread-safety of the reference_counter class.
        //       Multiple threads decrement the counter concurrently until it reaches
        //       the expected use count. The test ensures that the final count is correct,
        //       demonstrating that the reference_counter handles concurrent operations
        //       without data races or inconsistencies.
        constexpr size_t _Expected_use_count = 16;
        const size_t _Thread_count           = (::std::min)(4U, ::std::thread::hardware_concurrency());
        ::std::vector<::std::thread> _Threads;
        reference_counter _Counter(64);
        ::std::atomic<bool> _Work_started(false);
        for (size_t _Thread = 0; _Thread < _Thread_count; ++_Thread) {
            _Threads.push_back(::std::thread(
                [&] {
                    _Work_started.wait(false, ::std::memory_order_relaxed); // wait until the work is started
                    while (_Counter.use_count() > _Expected_use_count) { // decrement the counter if possible
                        _Counter.decrement();
                    }
                }
            ));
        }

        _Work_started.store(true);
        _Work_started.notify_all();
        for (::std::thread& _Thread : _Threads) {
            if (_Thread.joinable()) { // join the threads to avoid a std::terminate() call
                _Thread.join();
            }
        }

        EXPECT_LE(_Counter.use_count(), _Expected_use_count);
    }
} // namespace mjx