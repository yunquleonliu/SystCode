# Embedded Software 101 Curriculum

A structured roadmap for mastering embedded systems programming, from bare-metal basics to advanced RTOS and driver development.

## Module 1: Bare Metal Essentials & Architecture (10 Problems)
Focus: Startup, assembly interfacing, and direct hardware manipulation.

1.  **C Runtime Initialization (CRT0)**: Implement the startup code that initializes the `.bss` and `.data` segments before `main()`.
2.  **Linker Script Basics**: Write a linker script to place code in Flash and data in RAM.
3.  **Memory Map Layout**: Define specific memory regions for stack, heap, and shared memory in the linker file.
4.  **Register Bit Manipulation**: Create a type-safe register abstraction (using `volatile`, bit-fields, or macros) for a hypothetical peripheral.
5.  **Inline Assembly & Intrinsics**: Use assembly for special instructions (e.g., `NOP`, `WFI`, or finding the first set bit).
6.  **Stack Paint**: Implement a function to fill the stack with a pattern to measure usage at runtime.
7.  **Endianness Handling**: Write code to detect and handle data endianness dynamically or statically during compile time.
8.  **Unaligned Access Handling**: Implement a fault handler or wrapper for unaligned memory accesses.
9.  **Function Call Conventions (ABI)**: Manually parse the stack frame to retrieve arguments of a previous function call.
10. **Vector Table Setup**: Define and relocate an interrupt vector table in C.

## Module 2: Peripheral Driver Development (15 Problems)
Focus: Interfacing with standard hardware blocks.

11. **GPIO Driver**: Implement a generic GPIO driver with set/clear/toggle and input buffering.
12. **UART Polling Driver**: Write a simple blocking UART transmitter and receiver.
13. **UART Interrupt-Based Ring Buffer**: Upgrade the UART driver to use a circular buffer and interrupts.
14. **Simple Timer/Counter**: Configure a hardware timer to generate periodic events.
15. **PWM Generation**: Use a timer to generate a PWM signal for LED dimming or motor control.
16. **Watchdog Timer (WDT)**: Implement a mechanism to refresh the watchdog and debug a simulated "hang".
17. **I2C Bit-Banging**: Implement the I2C protocol using GPIO bit-banging.
18. **I2C Hardware Master**: Driver for a hardware I2C peripheral (read/write registers of a sensor).
19. **SPI Master Polling**: Basic SPI exchange function.
20. **ADC Single Conversion**: Read an analog value from a sensor.
21. **ADC DMA Transfer**: Configure DMA to read a sequence of ADC samples into a buffer automatically.
22. **Debounce Logic**: Implement a software state machine to debounce a mechanical button.
23. **Rotary Encoder Decoder**: Decode quadrature signals from a rotary encoder using interrupts or polling.
24. **Keypad Scanner**: Matrix keypad scanning algorithm.
25. **LCD/OLED Driver**: Basic character or frame buffer driver for a display (e.g., HD44780 or SSD1306) over I2C/SPI.

## Module 3: RTOS Concepts & Kernel Design (20 Problems)
Focus: Building a mini-RTOS or understanding OS internals (like VxWorks/FreeRTOS).

26. **Cooperative Scheduler**: Implement a simple run-to-completion task scheduler.
27. **Round-Robin Time Slicing**: Implement preemptive switching using a hardware timer tick.
28. **Task Control Block (TCB)**: Define the structure to hold task state (stack pointer, status, priority).
29. **Context Switch (Assembly)**: Save and restore CPU registers (R0-R15, PSR) during a task switch.
30. **Priority-Based Scheduling**: Implement a scheduler that always picks the highest priority ready task.
31. **Idle Task**: Implement the background task that runs when no other work is pending (and enters sleep).
32. **Semaphore (Binary)**: Implement a blocking binary semaphore.
33. **Counting Semaphore**: Extend the semaphore to handle resources with count > 1.
34. **Mutex with Priority Inheritance**: Simulate priority inversion and fix it with priority inheritance.
35. **Message Queue**: Implement a thread-safe FIFO queue for passing data between tasks.
36. **Event Flags/Groups**: Implement a mechanism for tasks to wait on single or multiple bit-flags.
37. **Software Timers**: Manage a list of software timers driven by a single hardware tick.
38. **Memory Pool (Fixed Block)**: Implementing a deterministic O(1) memory allocator for the OS.
39. **Worker/Bottom-Half threads**: Offload ISR work to a high-priority task.
40. **Tickless Idle**: Calculate how long the OS can sleep before the next timer event to save power.
41. **Deadlock Detection**: Runtime monitoring to detect circular dependencies between tasks.
42. **Stack Overflow Check**: Check stack canaries during context switch.
43. **CPU Load Monitor**: Calculate CPU usage percentage per task.
44. **Reentrancy Lab (The Gauntlet)**: Create a driver that fails under preemption (race condition), then fix it using Mutex, Critical Sections, and Lock-Free methods.
45. **Critical Sections**: Implement `ENTER_CRITICAL` and `EXIT_CRITICAL` disabling interrupts safely (nesting support).

## Module 4: Advanced Concurrency & Real-Time (10 Problems)
Focus: Determinism and complex synchronization.

46. **Reader-Writer Lock (RTOS)**: Prioritize readers or writers in an embedded context.
47. **Condition Variables**: Implement `wait` and `signal` semantics.
48. **Barrier Synchronization**: Wait for N tasks to reach a point.
49. **Rate Monotonic Scheduling (RMS)**: Verify schedulability of a periodic task set theoretically.
50. **Earliest Deadline First (EDF)**: Implement dynamic priority scheduling based on deadlines.
51. **Dual-Core Spinlock**: Implement specialized locking for multi-core AMP/SMP systems.
52. **Inter-Processor Communication (IPC)**: Shared memory ring buffer between two cores.
53. **Interrupt Latency Measurement**: Measure the time from HW trigger to ISR entry using GPIO.
54. **Jitter Analysis**: Measure the variation in periodic task execution.
55. **Priority Ceiling Protocol**: Alternative to inheritance for avoiding inversion.

## Module 5: Memory & Storage (10 Problems)
Focus: Flash, EEPROM, and filesystem abstractions.

56. **Flash Driver**: Implement Erase/Program operations for internal/external NOR flash.
57. **EEPROM Emulation**: Implement key-value storage over raw flash pages (wear leveling basics).
58. **Circular Log/Journal**: Append-only logging system for crash diagnostics.
59. **CRC32 Checksum**: Implement fast table-based CRC for data integrity.
60. **LittleFS/FatFS Porting**: Create the block device input/output shim for a filesystem.
61. **Memory Protection Unit (MPU)**: Configure MPU regions to detect stack overflows or code injection.
62. **Cache Coherency**: Manually invalidate/clean cache lines before/after DMA transfers.
63. **Scatter-Gather DMA**: Set up a linked-list based DMA transfer for scattered memory buffers.
64. **Heap Fragmentation Analysis**: Simulate alloc/free patterns to measure fragmentation.
65. **NAND Bad Block Management**: Basic table to map out bad blocks.

## Module 6: Communication Protocols & Networking (15 Problems)
Focus: Implementation of standard protocols.

66. **UART Command Shell (CLI)**: Implement a command parser with arguments.
67. **XMODEM/YMODEM Protocol**: Implement file transfer over UART.
68. **Modbus RTU Slave**: Implement the state machine for Modbus request/response.
69. **CAN Bus Filter**: Configure hardware filters for CAN ID acceptance.
70. **CAN-FD Payload**: Handle variable length payloads in CAN-FD.
71. **Ethernet Frame Builder**: Manually construct an Ethernet II frame (MAC header + payload).
72. **ARP Request/Reply**: Implement the Address Resolution Protocol state machine.
73. **IP/ICMP Stack**: Handle Ping (Echo Request) in a bare-metal stack.
74. **UDP Socket primitive**: Send and receive UDP packets.
75. **TCP State Machine (Simplified)**: Implement the handshake (SYN, SYN-ACK, ACK).
76. **MQTT Packet Serializer**: Encode a CONNECT and PUBLISH packet for IoT.
77. **CoAP Message**: Construct a constrained application protocol message.
78. **USB HID Mouse**: Simulate a USB mouse movement (Device descriptor setup).
79. **USB CDC-ACM**: Implement a virtual serial port over USB.
80. **Bluetooth LE Beacon**: Setup advertising data packet structure.

## Module 7: Bootloader & Security (10 Problems)
Focus: System startup reliability and firmware updates.

81. **Simple Bootloader**: Checking a GPIO on boot to decide whether to jump to App or stay.
82. **Firmware Image Header**: Define a struct for versioning, CRC, and entry point at a fixed offset.
83. **Memory Remapping/Aliasing**: Switch the vector table from Bootloader to Application.
84. **Firmware Update (Over-the-Air/UART)**: Receive chunks, write to flash, verify, and swap.
85. **Dual-Bank Boot**: Implement A/B partition logic for safe updates (rollback support).
86. **Secure Boot Chain (Concept)**: Verify a digital signature (RSA/ECDSA) of the image before booting.
87. **Root of Trust**: Lock JTAG/SWD access (simulated logic).
88. **Encrypted Storage**: AES-128/256 encryption for sensitive config data.
89. **True Random Number Generator (TRNG)**: Driver and entropy health check.
90. **Anti-Tamper**: Logic to wipe keys if a tamper event (switch opened) is detected.

## Module 8: DSP & Control (5 Problems)
Focus: Mathematical processing on microcontrollers.

91. **Fixed-Point Arithmetic**: Implement math libraries for processors without FPU.
92. **PID Controller**: Implement a Proportional-Integral-Derivative controller loop.
93. **Digital Filter (FIR/IIR)**: Implement a simple low-pass or high-pass filter.
94. **FFT (Fast Fourier Transform)**: Basic implementation or usage of CMSIS-DSP.
95. **Sensor Fusion (Complementary Filter)**: Combine Accelerometer and Gyroscope data.

## Module 9: Testing & DevOps (6 Problems)
Focus: Tools and automated testing.

96. **Semihosting**: Redirect `printf` to the debugger console.
97. **Fault Injection Hook**: Simulate a hardware error (bit flip) to test recovery.
98. **Unit Testing (Unity/CppUTest)**: Write a test for a driver with hardware mocking.
99. **Code Coverage (GCOV)**: Run embedded code on host (x86) to measure coverage.
100. **CI/CD Pipeline Script**: Write a script to build and run static analysis (Cppcheck) automatically.
101. **System Trace (SWV/ETM)**: Configure trace output for profiling or variable watching.

## Module 10: Special Topic - High Performance I/O (SmartNIC / Infiniband)
Focus: Advanced driver concepts for high-throughput packet processing.

102. **PCIe Enumeration & BAR Mapping**: Manually scan the PCI bus, find a specific Vendor/Device ID, and map its Base Address Registers (BARs) to userspace.
103. **SmartNIC Initialization (Mailbox)**: Implement the Admin Queue / Mailbox command interface to shake hands with firmware.
104. **Ring Doorbell Mechanism**: implement the "Producer Index" update via MMIO to notify hardware of new work.
105. **Scatter-Gather Descriptor Chain**: Construct a complex descriptor chain for zero-copy packet transmission.
106. **Interrupt Moderation (NAPI)**: Implement a hybrid polling/interrupt loop to handle high packet rates without ISR storms.
