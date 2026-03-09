#include <stdint.h>
#include <stdio.h>
#include <string.h>

// --- Simulated Memory Map -------------------------------------------------
#define FLASH_BASE 0x08000000
#define RAM_BASE   0x20000000
#define STACK_TOP  0x20002000 // 8KB RAM

// These symbols are typically defined by the LINKER SCRIPT.
// But we simulate them here as external symbols for C.
extern __attribute__((weak)) uint32_t _sidata[]; // Start of initialized data (in Flash)
extern __attribute__((weak)) uint32_t _sdata[];  // Start of initialized data (in RAM)
extern __attribute__((weak)) uint32_t _edata[];  // End of initialized data (in RAM)
extern __attribute__((weak)) uint32_t _sbss[];   // Start of .bss (in RAM)
extern __attribute__((weak)) uint32_t _ebss[];   // End of .bss (in RAM)

// --- Simulated Application Global Variables -------------------------------
volatile int g_initialized_var = 0xCAFEBABE; // Should be in .data
volatile int g_uninitialized_var;            // Should be in .bss (zeroed)

int main(void) {
    printf("--- Application Start ---\n");
    printf("g_initialized_var (expect 0xCAFEBABE): 0x%X\n", g_initialized_var);
    printf("g_uninitialized_var (expect 0): %d\n", g_uninitialized_var);

    if (g_initialized_var == 0xCAFEBABE && g_uninitialized_var == 0) {
        printf("SUCCESS: CRT0 Initialization Worked!\n");
        return 0;
    } else {
        printf("FAILURE: Data not initialized correctly.\n");
        return -1;
    }
}

// --- The Problem: Implement This Function ---------------------------------

/*
   The Reset Handler is the first code executed by the CPU.
   
   Your Task:
   1. Initialize stack pointer (implicit in C function entry usually, but good to know).
   2. Copy data from Flash (_sidata) to RAM (_sdata ... _edata).
   3. Zero out the BSS section (_sbss ... _ebss).
   4. Call SystemInit() (optional).
   5. Call main().
*/
void Reset_Handler(void) {
    // 1. Copy .data from Flash to RAM
    uint32_t *src = _sidata;
    uint32_t *dst = _sdata;
    
    // Simulate copying loop...
    // while (dst < _edata) {
    //     *dst++ = *src++;
    // }

    // 2. Zero .bss
    // dst = _sbss;
    // while (dst < _ebss) {
    //     *dst++ = 0;
    // }

    // 3. Call main
    main();
}

// --- Simulation Harness (Don't Edit Below) --------------------------------

// Mocking the Linker Script behavior manually for testing on PC
uint32_t _sidata[2] = { 0xCAFEBABE, 0xDEADBEEF }; // In "Flash"
uint32_t _sdata[2];   // In "RAM" (uninit)
uint32_t _edata[0];   // End marker (implicitly after _sdata)
uint32_t _sbss[2];    // In "RAM" (dirty)
uint32_t _ebss[0];    // End marker

// Override symbols to point to our mock arrays
// (This is a trick to run bare-metal logic on a host OS)
#undef _sidata
#undef _sdata
#undef _sbss
/* 
   NOTE: In a real system, you rely on the linker script to set these addresses.
   Here we trick the compiler to use our local arrays as the memory regions.
*/

int main_simulated() {
    // Dirty the RAM before reset to simulate random power-up state
    _sdata[0] = 0x12345678; 
    _sbss[0]  = 0x99999999; 

    printf("--- Power On Reset ---\n");
    printf("RAM Data (Before): 0x%X\n", _sdata[0]);
    printf("RAM BSS  (Before): 0x%X\n", _sbss[0]);

    // Manually call Reset Handler
    Reset_Handler(); 
    return 0;
}
