# Problem 36: Reflection in C

## Description
Use macro magic or DWARF parsing to print struct field names at runtime.

## Learning Objectives
- **Concepts**: Preprocessor Metaprogramming, Offsetof, Type Traits

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
The C reflection system uses macro-based metadata generation to create type descriptors with field names, offsets, and types. By defining structs through macros that both declare the struct and generate reflection tables, the code enables runtime type introspection, field enumeration, and generic serialization/deserialization in C.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/36_reflection_c/solution.c)**
