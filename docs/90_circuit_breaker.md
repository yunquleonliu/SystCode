# Problem 90: Circuit Breaker

## Description
State machine to fail fast when downstream service is down.

## Learning Objectives
- **Concepts**: Failure counting, State Transitions (Open/Closed/Half), Recovery

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
The circuit breaker pattern prevents cascading failures by monitoring service call failures and temporarily blocking requests when thresholds are exceeded. It transitions through states (Closed, Open, Half-Open), implements exponential backoff, tests recovery with limited requests, and provides fast-fail behavior to protect degraded downstream services.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/90_circuit_breaker/solution.c)**
