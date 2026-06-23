#!/usr/bin/env bash
set -euo pipefail

cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build -j

echo "Running demo..."
./build/cpsys_demo

echo "Running smoke test..."
./build/smoke_test

echo "Running benchmark..."
./build/register_access_bench

if command -v perf >/dev/null 2>&1; then
  echo "Running perf stat..."
  perf stat ./build/register_access_bench
else
  echo "perf not found; skipping perf stat"
fi
