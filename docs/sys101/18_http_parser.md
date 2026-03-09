# Problem 18: HTTP/1.1 Parser

## Description
Create a state-machine based parser for HTTP/1.1 request headers.

## Learning Objectives
- String parsing
- Finite State Machines (FSM)
- Robustness

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
state = METHOD
     char c = read()
     
     switch(state):
         case METHOD:
             if c == ' ': state = URL
             else append method
         case URL:
             if c == ' ': state = PROTOCOL
     ...
```


## Why This Problem Matters
- **HTTP/1.1 Parser** appears in real systems as a building block for reliability, performance, or scalability.
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
The HTTP parser implements a finite state machine that transitions through states (METHOD, URL, PROTOCOL, HEADERS) based on input characters. It accumulates tokens in each state, transitions on delimiters (spaces, newlines, colons), and builds a structured representation of the HTTP request with method, URL, protocol version, and header key-value pairs.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/18_http_parser/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Parse 'GET / HTTP/1.1'**
- **Extract headers to Key-Value map**
- **Handle malformed requests**
