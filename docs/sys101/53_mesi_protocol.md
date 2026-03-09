# Problem 53: Cache Coherency (MESI)

## Description
Simulate state transitions of Modified, Exclusive, Shared, Invalid cache lines.

## Learning Objectives
- **Concepts**: State Machines, Bus Snooping, Write-Back vs Write-Through

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
The MESI cache coherence protocol simulation tracks cache line states (Modified, Exclusive, Shared, Invalid) across multiple CPU caches. It handles read/write requests by sending bus transactions (BusRd, BusRdX), transitions states based on observed operations, and ensures memory consistency in multiprocessor systems by invalidating or updating remote caches.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/53_mesi_protocol/solution.c)**
