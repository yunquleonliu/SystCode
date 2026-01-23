# Problem 56: Watchdog Timer

## Description
Implement a system health monitor that resets if not 'kicked'.

## Learning Objectives
- **Concepts**: Timeouts, System Reliability, Heartbeats

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
The watchdog timer monitors system health by requiring periodic "petting" (timer resets) from the monitored application. If the timer expires without being reset, it triggers recovery actions (restart, alert). This implementation demonstrates fault detection and automatic recovery mechanisms for detecting hung processes or deadlocks.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/56_watchdog_timer/solution.c)**
