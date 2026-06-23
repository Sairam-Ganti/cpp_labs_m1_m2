# C++ Systems Lab

A small C++ systems/performance lab for practicing clean model design, register-style interfaces, descriptor queues, data movement simulation, completion tracking, and basic profiling.

## Goals

This repository is intentionally small and generic. It is meant to build comfort with:

- Modern C++ ownership and lifetime management
- Register-style interfaces
- Descriptor-based command submission
- Queue and completion handling
- Simple data movement simulation
- Performance counters
- Benchmarking and profiling workflow
- Clear technical documentation

## Non-goals

This repository does not implement a real hardware protocol, production driver, device stack, or vendor-specific behavior. All names, registers, descriptors, and flows are synthetic.

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build -j
```

## Run

```bash
./build/cpsys_demo
./build/smoke_test
./build/register_access_bench
```

## Suggested workflow

1. Start with the demo.
2. Read the `include/cpsys/` interfaces.
3. Run the smoke test.
4. Run the benchmark.
5. Record observations in `notes/week01.md`.

## Repository layout

```text
cpp-systems-lab/
  include/cpsys/        Public headers
  src/                  Implementation and demo
  tests/                Lightweight assertion tests
  benchmarks/           Small benchmark programs
  docs/                 Concept notes and project writeups
  notes/                Weekly execution notes
  interview/            Question bank
  scripts/              Helper scripts
```

## Current starter components

- `RegisterMap`: simple 32-bit offset-based register interface
- `RingQueue`: bounded circular queue
- `SimpleDevice`: synthetic descriptor processor
- `PerfCounters`: lightweight counters for submitted/completed work
