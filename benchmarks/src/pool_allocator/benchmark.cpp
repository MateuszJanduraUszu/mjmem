// benchmark.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <benchmark/benchmark.h>
#include <mjmem/pool_allocator.hpp>
#include <mjmem/pool_resource.hpp>

namespace mjx {
    inline constexpr size_t _Block_size = 16;

    template <size_t _Res_size>
    bool allocate_pool_allocator() {
        // Note: The pool_allocator is designed to be indifferent to individual block deallocations.
        //       It deallocates the entire main block when destroyed, making it safe to omit
        //       deallocation of memory allocated by pool_allocator::allocate() in this case.
        pool_resource _Res(_Res_size);
        pool_allocator _Al(_Res);
        constexpr size_t _Count = _Res_size / _Block_size; // number of iterations
        for (size_t _Idx = 0; _Idx < _Count; ++_Idx) {
            _Al.allocate(_Block_size); // allocate 16-byte block
        }

        return true; // must return anything for benchmark::DoNotOptimize()
    }

    template <size_t _Res_size>
    void bm_allocate_pool_allocator(::benchmark::State& _State) {
        for (const auto& _Step : _State) {
            ::benchmark::DoNotOptimize(allocate_pool_allocator<_Res_size>());
        }
    }
} // namespace mjx

void set_benchmark_properties(auto* const _Benchmark) {
    _Benchmark->DenseRange(1, 10)->Unit(::benchmark::TimeUnit::kNanosecond);
}

BENCHMARK(::mjx::bm_allocate_pool_allocator<128>)->Apply(set_benchmark_properties);
BENCHMARK(::mjx::bm_allocate_pool_allocator<256>)->Apply(set_benchmark_properties);
BENCHMARK(::mjx::bm_allocate_pool_allocator<512>)->Apply(set_benchmark_properties);
BENCHMARK(::mjx::bm_allocate_pool_allocator<1024>)->Apply(set_benchmark_properties);
BENCHMARK(::mjx::bm_allocate_pool_allocator<2048>)->Apply(set_benchmark_properties);
BENCHMARK(::mjx::bm_allocate_pool_allocator<4096>)->Apply(set_benchmark_properties);
BENCHMARK(::mjx::bm_allocate_pool_allocator<8192>)->Apply(set_benchmark_properties);

BENCHMARK_MAIN();