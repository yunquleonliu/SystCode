# Problem 13: ELF Header Parser

## Description
Write a parser to read an ELF binary and extract the entry point address and segment info.

## Learning Objectives
- Binary formats
- Struct padding
- Endianness

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
read_elf(file):
         read(header, sizeof(Elf64_Ehdr))
         check magic bytes (0x7F 'E' 'L' 'F')
         print "Entry point:", header.e_entry
         
         seek(header.e_phoff)
         for i in 0..e_phnum:
             read(phdr)
             if phdr.type == PT_LOAD:
                 print segment details
```

## Testing Standards
Your solution must pass the following test scenarios:
- **Identify valid ELF file**
- **Print correct entry point**
- **Reject invalid magic bytes**
