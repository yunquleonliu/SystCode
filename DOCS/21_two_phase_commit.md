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

## Testing Standards
Your solution must pass the following test scenarios:
- **Commit scenario: All vote Yes**
- **Abort scenario: One votes No**
- **Coordinator timeout**
