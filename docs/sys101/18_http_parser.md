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

## Solution Summary
The HTTP parser implements a finite state machine that transitions through states (METHOD, URL, PROTOCOL, HEADERS) based on input characters. It accumulates tokens in each state, transitions on delimiters (spaces, newlines, colons), and builds a structured representation of the HTTP request with method, URL, protocol version, and header key-value pairs.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/18_http_parser/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Parse 'GET / HTTP/1.1'**
- **Extract headers to Key-Value map**
- **Handle malformed requests**
