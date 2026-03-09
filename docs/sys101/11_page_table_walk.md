# Problem 11: Page Table Walk

## Description
Simulate the hardware page table walk mechanism for translating virtual addresses.

## Learning Objectives
- Bit masking
- Multi-level page tables
- Memory virtualization

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
translate(vpn):
         L1_index = (vpn >> 22) & 0x3FF
         L2_index = (vpn >> 12) & 0x3FF
         
         pte1 = phys_mem[CR3 + L1_index]
         if not present(pte1): fault()
         
         pte2 = phys_mem[pte1.frame + L2_index]
         if not present(pte2): fault()
         
         return pte2.frame
```


## Why This Problem Matters
- **Page Table Walk** appears in real systems as a building block for reliability, performance, or scalability.
- Mastering this problem improves your ability to reason about low-level tradeoffs under constraints.

## Step-by-Step Tutoring Guide
1. **Model first**: define invariants and expected state transitions before coding.
2. **Minimal baseline**: implement the simplest correct path.
3. **Harden edges**: handle boundary inputs, error propagation, and cleanup paths.
4. **Optimize last**: tune only after tests prove behavior.

## Common Pitfalls
- Treating happy-path correctness as enough.
- Missing ownership/lifetime rules for memory or resources.
- Ignoring concurrent access patterns and race windows.
- Over-optimizing without measurements.

## Debug & Validation Checklist
- Verify invariants after every major operation.
- Add targeted tests for boundary and stress cases.
- Inspect failure paths as carefully as success paths.
- Confirm complexity/latency assumptions with simple measurements.

## Further Practice
1. Implement a second variant with a different tradeoff (speed vs clarity).
2. Add instrumentation counters for visibility.
3. Document one production-style failure mode and mitigation.

## Solution Summary
The page table walk simulation extracts multi-level indices from virtual addresses using bit masking and shifting, then traverses the page table hierarchy to translate virtual addresses to physical frames. The implementation checks present bits at each level and handles page faults for unmapped addresses, mimicking hardware MMU behavior.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/11_page_table_walk/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Correct translation of mapped address**
- **Fault on unmapped address**
- **Permission bits check**
