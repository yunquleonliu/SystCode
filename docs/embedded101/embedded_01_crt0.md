# Problem: C Runtime Initialization (CRT0)

## Description

In a bare-metal embedded system, there is no Operating System to load your program. When power is applied, the CPU jumps to the Reset Vector. 
Your job is to write the code that executes *before* `main()`.

This code is often called `crt0.s` (C RunTime 0) or `startup.c`. 
It must:
1.  **Initialize the Stack Pointer (SP)**.
2.  **Copy .data**: Move initialized global variables from Flash (Load Address) to RAM (Execution Address).
3.  **Zero .bss**: Clear uninitialized global variables in RAM to zero.
4.  **Call System Init**: Configure clocks/watchdogs (optional).
5.  **Call main()**: Jump to the application entry point.

## Requirements

1.  Write a simple linker script `linker.ld` (or mock struct) defining `_sdata`, `_edata`, `_sbss`, `_ebss`, `_sidata`.
2.  Implement `Reset_Handler` in C (or Assembly if you prefer).
3.  Demonstrate that variables declared as `int foo = 42;` (data) and `int bar;` (bss) are correctly initialized before `main` runs.

## Hint

*   Symbols like `_sdata` are addresses provided by the *linker*, not variables. Use `&_sdata` in C.
*   The `.data` section is stored in Flash (LMA - Load Memory Address) but must be copied to RAM (VMA - Virtual Memory Address).
