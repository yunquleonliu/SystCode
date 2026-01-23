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

## Testing Standards
Your solution must pass the following test scenarios:
- **Correct translation of mapped address**
- **Fault on unmapped address**
- **Permission bits check**
