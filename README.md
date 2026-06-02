# bench

Minimal CMake project that pulls in [Google Benchmark](https://github.com/google/benchmark)
via `FetchContent` and benchmarks two functions to see how they scale with input size.


## Build & run

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/bench_main          # on Windows: build\Release\bench_main.exe
```

