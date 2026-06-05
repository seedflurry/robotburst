# RobotBurst

[![RobotBurst](robotburst.jpg)](https://github.com/williamstaffordparsons/robotburst)

## Table of Contents

- [Introduction](README.md?tab=readme-ov-file#introduction)
- [Author](README.md?tab=readme-ov-file#author)
- [Reference](README.md?tab=readme-ov-file#reference)
- [Benchmarks](README.md?tab=readme-ov-file#benchmarks)

## Introduction

RobotBurst is a hyper-efficient cryptographic PRNG (for 64-bit architecture) that has a minimum period of at least 2⁶⁴, hyper-fast speed, low-footprint code and parallelism.

While RobotBurst may be suitable for some implementations as-is, it's very much a work-in-progress that I need to evaluate (and modify accordingly) for years before releasing (to satisfy the burden of cryptographic proof and improve both speed and randomness quality to the absolute peak).

## Author

RobotBurst was created by me, [William Stafford Parsons](https://github.com/williamstaffordparsons) <<williamstaffordparsons@proton.me>>.

## Motivation

As an enjoyer of video games, it was brought to my attention that high-fidelity 3D graphics algorithms (such as ambient occlusion and path tracing) decrease game engine rendering performance partially due to the massive overhead of generating up to billions of pseudorandom numbers (per second) with slow CSPRNGs.

As a solution, I'm building RobotBurst as the ultimate 64-bit CSPRNG to outperform (in as many ways as possible) the fastest 64-bit CSPRNGs in the world.

## Reference

RobotBurst was implemented in C (requiring the `stdint.h` header to define a 64-bit, unsigned integral type for `uint64_t`).

[robotburst.c](robotburst.c)

#### `robotburst256`

The `robotburst256` function modifies the state in a `struct robotburst256_state` instance to generate 4 pseudorandom `uint64_t` integers in the `output` array.

Each state variable (`a`, `b`, `c`, `d`, `e` and `f`) in a `struct robotburst256_state` instance must be seeded before generating a deterministic `robotburst256` sequence.

## Benchmarks

Each of the following results log the fastest process execution speed (in milliseconds) among several repetitions of a CSPRNG speed test (using `gcc -O3` from an AMD A4-9120C) that generates (and hashes) 1 billion pseudorandom `uint64_t` integers in a `#pragma GCC unroll 0` loop.

| PRNG | Elapsed |
| --- | --- |
| **`robotburst256`** | **3586ms** |
| `aes_ni_ctr_128` (`-maes -msse4`) | 3796ms |
