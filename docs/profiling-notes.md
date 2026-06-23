# Profiling Notes

Record commands, observations, and results here.

## Build mode

Use:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build -j
```

## Basic commands

```bash
./build/cpsys_demo
./build/register_access_bench
```

## Linux profiling examples

```bash
perf stat ./build/register_access_bench
perf record ./build/register_access_bench
perf report
```

## Questions to answer

- Which function dominates runtime?
- Are results stable across runs?
- Did optimization level change the result?
- Is the benchmark measuring the intended behavior?
- What changed after the code was refactored?
