# Problem 17: Endianness Swap

## Description
Implement a function to swap byte order for 64-bit integers.

## Learning Objectives
- Bitwise shifts
- Masks
- Byte ordering

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
swap64(val):
         return ((val & 0xFF) << 56) |
                ((val & 0xFF00) << 40) |
                ... 
                ((val >> 56) & 0xFF)
```

## Testing Standards
Your solution must pass the following test scenarios:
- **Convert Little Endian to Big Endian**
- **Verify 0x12345678... transformation**
- **Identity on symmetric bytes**
