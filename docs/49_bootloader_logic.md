# Problem 49: Bootloader Logic

## Description
Simulate loading a kernel from disk to memory and jumping to entry.

## Learning Objectives
- **Concepts**: A20 Line, Segment Registers, 16-bit to 32-bit switch

## Implementation Guide
1. **Understand Layout**: Review how this component works in a real system.
2. **Define Structures**: Create the `struct` needed.
3. **Core Logic**: Implement the algorithm.
4. **Edge Cases**: Handle memory boundaries, overflows, or concurrency.

## Testing Strategy
- Verify fundamental correctness.
- Test boundary conditions.
- (If applicable) Performance benchmark.

## Pseudocode Hint
```text
// Add high-level logic here
```

## Solution Summary
The bootloader logic loads the kernel from disk into memory and transfers control to it. Written in assembly for the boot sector, it uses BIOS interrupts to read disk sectors, relocates the kernel to the correct memory address, sets up minimal CPU state (stack, segment registers), and jumps to the kernel entry point.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/49_bootloader_logic/solution.c)**
