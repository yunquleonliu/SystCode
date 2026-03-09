# Problem 21: 2PC (Two-Phase Commit)

## Description
Simulate the Two-Phase Commit protocol for distributed transactions.

## Learning Objectives
- Consensus
- State machines
- Failure modes

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
Coordinator:
         send PREPARE to all
         wait for VOTES
         if all YES:
             send COMMIT
         else:
             send ABORT
             
     Participant:
         on PREPARE:
             lock resources
             return YES/NO
         on COMMIT/ABORT:
             apply/rollback
             unlock
```


## Why This Problem Matters
- **2PC (Two-Phase Commit)** appears in real systems as a building block for reliability, performance, or scalability.
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
The Two-Phase Commit implementation simulates a coordinator sending PREPARE messages to participants, collecting votes, and deciding to COMMIT (if all YES) or ABORT (if any NO). Participants lock resources during the prepare phase and apply or rollback changes based on the coordinator's decision, ensuring atomic distributed transactions with proper timeout handling.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/21_two_phase_commit/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Commit scenario: All vote Yes**
- **Abort scenario: One votes No**
- **Coordinator timeout**
