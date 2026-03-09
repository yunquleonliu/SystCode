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

## Solution Summary
The Two-Phase Commit implementation simulates a coordinator sending PREPARE messages to participants, collecting votes, and deciding to COMMIT (if all YES) or ABORT (if any NO). Participants lock resources during the prepare phase and apply or rollback changes based on the coordinator's decision, ensuring atomic distributed transactions with proper timeout handling.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/21_two_phase_commit/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Commit scenario: All vote Yes**
- **Abort scenario: One votes No**
- **Coordinator timeout**
