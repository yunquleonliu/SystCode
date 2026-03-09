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

## Solution Summary
The endianness swap function uses bitwise shifts and masks to reverse the byte order of 64-bit integers. Each byte is extracted using masks (0xFF, 0xFF00, etc.), shifted to its new position, and combined using bitwise OR to convert between little-endian and big-endian representations for network byte order conversions.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/17_endianness_swap/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Convert Little Endian to Big Endian**
- **Verify 0x12345678... transformation**
- **Identity on symmetric bytes**
