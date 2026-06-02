#include <benchmark/benchmark.h>

#include <numeric>
#include <vector>

#include "mylib.h"

static std::vector<int> make_input(int n) {
    std::vector<int> data(n);
    std::iota(data.begin(), data.end(), 0);
    return data;
}

// A benchmark is just a function taking `benchmark::State&`. The framework
// calls it once per input size; `state` carries the current input parameter
// in and collects timing/complexity results out.
static void BM_Sum(benchmark::State& state) {
    // state.range(0) is the first argument the framework picked for this run
    // (here, the input size set up by Range() below). Build the input ONCE,
    // outside the timing loop, so we don't measure allocation/fill cost.
    const auto data = make_input(static_cast<int>(state.range(0)));

    // The `for (auto _ : state)` loop is the measured region. Benchmark runs
    // the body many times (state decides how many, until the timing is
    // statistically stable) and times only what's inside this loop.
    for (auto _ : state) {
        // DoNotOptimize() tells the compiler "pretend this value is used,"
        // so it can't delete the call to sum() as dead code. Without it, an
        // optimizer may erase the whole benchmark and you'd time nothing.
        benchmark::DoNotOptimize(sum(data));
    }

    // SetComplexityN() records "the N for this run" so that, combined with
    // Complexity() below, the framework can fit a Big-O curve across all the
    // input sizes and print an estimated complexity (e.g. "0.13 N").
    state.SetComplexityN(state.range(0));

    // SetItemsProcessed() reports how many items we handled in total, letting
    // Benchmark print an items_per_second throughput column. iterations() is
    // how many times the loop above actually ran.
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
// BENCHMARK() registers the function so BENCHMARK_MAIN() will run it.
//   RangeMultiplier(2) -> step input sizes by powers of 2
//   Range(1<<6, 1<<16) -> run for N = 64, 128, 256, ... up to 65536
//   Complexity(oN)     -> expect/fit linear O(N); prints the measured fit + RMS
BENCHMARK(BM_Sum)->RangeMultiplier(2)->Range(1 << 6, 1 << 16)->Complexity(benchmark::oN);

static void BM_HasDuplicate(benchmark::State& state) {
    const auto data = make_input(static_cast<int>(state.range(0)));
    for (auto _ : state) {
        benchmark::DoNotOptimize(has_duplicate(data));
    }
    state.SetComplexityN(state.range(0));
}
// Same idea, but a smaller Range (up to 4096) because this is O(N^2) and gets
// slow fast. oNSquared tells the framework to fit an N^2 curve instead.
BENCHMARK(BM_HasDuplicate)->RangeMultiplier(2)->Range(1 << 6, 1 << 12)->Complexity(benchmark::oNSquared);


static void BM_Collatz(benchmark::State& state) {
    const auto data = make_input(static_cast<int>(state.range(0)));
    for (auto _ : state) {
        benchmark::DoNotOptimize(collatz(data));
    }
    state.SetComplexityN(state.range(0));
}
// Without this BENCHMARK() line, BM_Collatz is never registered and won't run.
// No Complexity() here, so it just reports raw Time/CPU per input size.
BENCHMARK(BM_Collatz)->RangeMultiplier(2)->Range(1 << 6, 1 << 12);


// BENCHMARK_MAIN() expands to a main() that parses --benchmark_* flags and
// runs every registered benchmark. Because of it, this file needs no main().
BENCHMARK_MAIN();
