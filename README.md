# bench

Minimal CMake project that pulls in [Google Benchmark](https://github.com/google/benchmark) and does benchmarks of some example functions.


## Build & run

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/bench_main          # on Windows: build\Release\bench_main.exe
```

