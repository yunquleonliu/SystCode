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

## Testing Standards
Your solution must pass the following test scenarios:
- **Parse 'GET / HTTP/1.1'**
- **Extract headers to Key-Value map**
- **Handle malformed requests**
