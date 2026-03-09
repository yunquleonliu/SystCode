# E005: Inline Assembly & Intrinsics

## Objective
- Learn how to access CPU-special instructions from C using compiler intrinsics and (optionally) inline assembly.
- Implement and compare two high-frequency bit operations:
	- 32-bit byte swap (endianness conversion)
	- leading-zero count (CLZ)
- Understand why intrinsics are usually the best balance between performance, portability, and readability.

## Background
- Module: Bare Metal Essentials & Architecture (10 Problems)
- Scope: Embedded systems docs-first specification before implementation.
- In embedded firmware, some operations are performance-critical and already supported by single CPU instructions.
- Typical examples in this exercise:
	- `__builtin_bswap32(x)` maps to byte-reverse instructions (e.g., ARM `REV`).
	- `__builtin_clz(x)` maps to leading-zero instructions (e.g., ARM `CLZ`).
- Using plain C logic for these can generate many instructions and branches, increasing latency and jitter in real-time paths.

## Requirements
- Provide both baseline C implementation and intrinsic-based implementation for each function.
- Verify correctness equivalence on representative vectors.
- Document architecture assumptions (ARM Cortex-M preferred, but support generic compiler fallback).
- Clarify behavior for `clz(0)` to avoid undefined behavior in C builtins.
- Keep APIs side-effect free (pure functions), deterministic, and safe in task/ISR contexts.

## Interfaces
- Input:
	- `uint32_t value` for both byte-swap and CLZ functions.
- Output:
	- `reverse_bytes_*`: returns swapped 32-bit value.
	- `count_leading_zeros_*`: returns integer in range `[0, 32]`.
- Error Handling:
	- No runtime error code.
	- Define `count_leading_zeros_* (0)` behavior explicitly as returning `32`.
	- If compiler builtin has undefined behavior for zero, guard with a branch before calling builtin.

## Tutorial Walkthrough

### 1) What this code is doing
- This exercise compares two implementation paths:
	- Pure C path: shift/mask/or or loop-based bit scan.
	- Intrinsic path: compiler builtins that map directly to target instructions.
- Core operation A: byte swap
	- Example: `0x12345678 -> 0x78563412`.
	- Common in network/protocol parsing (big-endian wire format vs little-endian memory layout).
- Core operation B: leading-zero count
	- Counts contiguous zeros from MSB toward LSB.
	- Common in RTOS scheduling bitmaps, normalization, and priority calculations.

### 2) How this maps to assembly
- On ARM (Cortex-M/Cortex-A), intrinsic code is expected to compile to single instructions:
	- byte swap: `REV`
	- leading zeros: `CLZ`
- Pure C version often compiles to multi-instruction sequences and may include branches.
- Verification method:
	- Compile with optimization (`-O2`/`-O3`).
	- Disassemble (`objdump -d` or compiler explorer).
	- Confirm the intrinsic version emits expected instruction forms.

### 3) Why intrinsics are preferred in firmware

| Approach | Performance | Portability | Readability | Typical Use |
|---|---|---|---|---|
| Pure C logic | Medium/Low | High | Medium | Functional fallback, reference implementation |
| Inline assembly (`__asm__`) | High | Low | Low | Architecture-specific hot spots when builtin unavailable |
| Intrinsics (`__builtin_*`) | High | Medium/High | High | Default recommendation |

- Key takeaway:
	- Don’t manually emulate operations already provided as native instructions unless portability constraints force it.
	- Prefer builtins with guarded fallbacks.

### 4) Edge cases and pitfalls
- `__builtin_clz(0)` is undefined in many compilers: always guard zero first.
- Keep function signatures unsigned (`uint32_t`) to avoid sign-extension confusion.
- Validate generated code at target optimization levels; debug builds may not show final instruction mapping.
- Avoid premature inline assembly if a builtin already maps cleanly to the same instruction.

## Reentrancy & Concurrency Notes
- Calling contexts: Task / ISR / SoftIRQ / SMP core are all allowed.
- Functions in this exercise should be pure and stateless.
- No shared mutable state, no locks, no memory allocation.
- Deterministic execution path required for real-time usage.

## Acceptance Criteria
- [ ] `reverse_bytes_c(x) == reverse_bytes_intrinsic(x)` for test vectors and random data.
- [ ] `count_leading_zeros_c(x) == count_leading_zeros_intrinsic(x)` for all tested values, including `0`.
- [ ] Intrinsic implementation disassembles to expected instruction forms on supported targets.
- [ ] No undefined behavior in zero-input CLZ path.
- [ ] Code is reentrant and safe in ISR context.

## Suggested Tests
1. Deterministic vectors:
	 - Byte swap: `0x00000000`, `0xFFFFFFFF`, `0x12345678`, `0xA5A5A5A5`.
2. CLZ edge vectors:
	 - `0` -> `32`, `1` -> `31`, `0x80000000` -> `0`, `0x00F00000` -> `8`.
3. Differential test:
	 - Compare C vs intrinsic across large pseudo-random input set.
4. Codegen validation:
	 - Ensure optimized build emits expected instruction mapping (`REV`, `CLZ`) where applicable.
5. Context safety:
	 - Invoke from simulated task and ISR wrappers to confirm no hidden dependencies.

## Reader Exercises (Optional)
1. Add 64-bit byte swap variant and compare codegen.
2. Implement `ctz` (count trailing zeros) with builtin and fallback.
3. Measure cycle counts on target board (DWT cycle counter or equivalent).

## Existing Detailed Draft
- This spec serves as the detailed draft for E005.

## Notes
- Related roadmap item: [embedded_software_roadmap.md](/embedded101/embedded_software_roadmap.md)

## Reference Implementation
- C source: [../../problems/embedded101/E005_inline_assembly_intrinsics/solution.c](https://github.com/yunquleonliu/SystCode/blob/main/problems/embedded101/E005_inline_assembly_intrinsics/solution.c)
