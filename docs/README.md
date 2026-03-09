# Q101 of Low Level System 🛠️

**"LeetCode for Systems Programming"**

Welcome to **Q101 of Low Level System**, a curated collection of **101 core systems programming challenges** covering Memory Management, Concurrency, OS Internals, Networking, Distributed Systems, High Performance Computing, and AI Infrastructure.

## 🚀 How to Use

### Prerequisites
- **GCC/Clang** or **MSVC** (C Compiler)
- **Make** (Optional, but recommended for the Makefile workflow)
- **Python 3** (For utility scripts)

### Getting Started
1. **Navigate** to a problem directory (e.g., `problems/01_aligned_malloc/`).
2. **Read** `solution.c` to understand the task and requirements.
3. **Implement** your solution in `solution.c`.
4. **Run** the tests.

#### Using via Makefile (Linux/WSL/MacOS)
To run the tests for a specific problem:
```bash
make run PROBLEM=01_aligned_malloc
```

#### Manual Compilation
If you don't have Make installed:
```bash
gcc -I./include -Wall -O2 problems/01_aligned_malloc/solution.c -o bin/test_runner
./bin/test_runner
```

---

## 🗺️ Roadmap & Curriculum

### Module 1: Memory Management (内存管理)
Master the art of manual memory manipulation and allocator design.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 1 | **[Aligned Malloc](01_aligned_malloc.md)** | Implement an allocator with custom alignment support. | Bitwise Ops, Pointer Arithmetic | ✅ |
| 2 | **[Memmove](02_memmove_overlap_safe.md)** | Safe memory copy handling overlapping regions. | Address Comparison, Reverse Copy | ⬜ |
| 3 | **[Arena Allocator](03_arena_allocator.md)** | Fixed-size memory pool with batch freeing. | Pointer Bump, O(1) Allocation | ⬜ |
| 4 | **[Buddy System](04_buddy_system.md)** | Kernel-style allocator for power-of-2 blocks. | Binary Trees, Block Merging/Splitting | ⬜ |
| 5 | **[Intrusive Ref Counting](05_reference_counting_intrusive.md)** | Smart pointer implementation embedded in data. | `offsetof`, Atomic Inc/Dec | ⬜ |

### Module 2: Concurrency & Sync (并发与同步)
Build synchronization primitives from scratch using atomics.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 6 | **[Spinlock (CAS)](06_spinlock_cas.md)** | User-space spinlock using atomic exchange. | `__atomic`, Busy-Wait Optimization | ⬜ |
| 7 | **[Lock-free Stack](../problems/07_lock_free_stack)** | Thread-safe stack without mutexes. | ABA Problem, CAS Loops | ⬜ |
| 8 | **[Thread Pool](../problems/08_thread_pool)** | Fixed-size worker pool for task execution. | Condition Variables, Task Queues | ⬜ |
| 9 | **[Read-Write Lock](../problems/09_read_write_lock)** | Implement a writer-preferred RW lock. | Starvation Prevention, State Flags | ⬜ |
| 10 | **[Barrier](../problems/10_barrier)** | Thread synchronization barrier. | Thread Counting, Release Points | ⬜ |

### Module 3: OS & Low-Level I/O (操作系统与底层 I/O)
Simulate core OS components and file operations.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 11 | **[Page Table Walk](../problems/11_page_table_walk)** | Simulate virtual to physical address translation. | Multi-level Pages, MMU Simulation | ⬜ |
| 12 | **[Mmap Copy](../problems/12_mmap_copy)** | High-perf file copy using memory mapping. | `mmap`, `msync`, Page Faults | ⬜ |
| 13 | **[ELF Parser](../problems/13_elf_header_parser)** | Parse binary headers to find entry points. | Struct Mapping, Endianness | ⬜ |
| 14 | **[Ring Buffer](../problems/14_ring_buffer)** | Lock-free circular buffer for IPC/Audio. | Producer/Consumer Indices, Modulo | ⬜ |
| 15 | **[User Context Switch](../problems/15_user_space_context_switch)** | Simulate coroutine context switching. | `setjmp`/`longjmp`, Register Save/Restore | ⬜ |

### Module 4: Networking (网络编程)
Implement foundational network protocols and servers.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 16 | **[Epoll Echo Server](../problems/16_epoll_echo_server)** | High-concurrency event-driven server. | ET vs LT, Non-blocking I/O | ⬜ |
| 17 | **[Endianness Swap](../problems/17_endianness_swap)** | Network byte order conversion for 64-bit ints. | Bit Shifts, Masking | ⬜ |
| 18 | **[HTTP/1.1 Parser](../problems/18_http_parser)** | Zero-copy HTTP header parsing. | FSM, String Optimization | ⬜ |
| 19 | **[TCP Flow Control](../problems/19_simple_tcp_flow_control)** | Simulate sliding window protocol. | Window Updates, ACKs | ⬜ |
| 20 | **[Raw Socket ICMP](../problems/20_raw_socket_icmp)** | Construct and send Ping packets manually. | Checksums, Raw Sockets | ⬜ |

### Module 5: Distributed Systems (分布式与协同)
Understand the algorithms that power cloud infrastructure.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 21 | **[2PC (Two-Phase Commit)](../problems/21_two_phase_commit)** | Distributed transaction coordinator simulation. | Prepare/Commit Phases, Timeouts | ⬜ |
| 22 | **[Consistent Hashing](../problems/22_consistent_hashing)** | Distributed cache node mapping. | Hash Ring, Virtual Nodes | ⬜ |
| 23 | **[Vector Clock](../problems/23_vector_clock)** | Causality tracking in distributed events. | Version Vectors, Partial Ordering | ⬜ |
| 24 | **[Gossip Protocol](../problems/24_gossip_protocol)** | Epidemic status propagation. | Randomized Fanout, Convergence | ⬜ |
| 25 | **[Raft Heartbeat](../problems/25_raft_heartbeat)** | Leader election heartbeat mechanism. | Timers, Lease Management | ⬜ |

### Module 6: Advanced OS Internals (Core OS Engineering)
The deep logic that decides "Who runs?" and "Where is data stored?".

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 26 | **[Round-Robin Scheduler](../problems/26_round_robin_scheduler)** | Runqueue simulation with time slicing. | Preemption, Quantum, Task States | ⬜ |
| 27 | **[Simple File System](../problems/27_simple_file_system)** | Inode-based FS implementation on a virtual disk. | Inodes, Bitmaps, Superblock | ⬜ |
| 28 | **[LSM-Tree](../problems/28_lsm_tree_storage)** | Log-Structured Merge Tree basics (Write path). | MemTable, SSTable, Write Amplification | ⬜ |
| 29 | **[Mini Container](../problems/29_mini_container)** | Process isolation using Namespaces. | `clone`, `unshare`, PID/Mount Namespace | ⬜ |
| 30 | **[Mini Debugger](../problems/30_mini_debugger)** | Tracer using `ptrace` syscall. | Registers, Breakpoints, System Calls | ⬜ |

---

## 🔮 Future Expansions
- **Compilers**: LLVM IR generation, Regex Engine.
- **Security**: Stack Overflow simulation, Crypto implementation.
- **Database**: B-Tree indices, LSM-Tree Log compaction, WAL.

---
*Happy Coding!*

### Module 7: Compiler & Runtime

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 31 | JIT Compiler (x64) | mmap PROT_EXEC, ABI calling convention, Instruction Encoding | Medium |
| 32 | Custom Dynamic Linker | ELF Dynamic Section, Relocation, Lazy Binding | Medium |
| 33 | Mark & Sweep GC | Stack scanning, Reachability Graph, Memory Reclamation | Medium |
| 34 | Address Sanitizer (Mini-ASan) | Shadow Memory mapping, Poison values, Instrumentation | Medium |
| 35 | Coroutines (State Machine) | State Machines, Macro Expansion, Reentrancy | Medium |
| 36 | Reflection in C | Preprocessor Metaprogramming, Offsetof, Type Traits | Medium |
| 37 | Linker Symbol Resolution | Symbol Tables, Weak/Strong definitions, Common blocks | Medium |
| 38 | Stack Unwinder | Stack Frames, RBP Register, Return Addresses | Medium |
| 39 | Function Hooking (Trampoline) | Code Patching, Relative Jumps, Instruction preservation | Medium |
| 40 | NaN Boxing | IEEE 754, Bitwise casting, Type Tagging | Medium |

### Module 8: Kernel & Virtualization

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 41 | Minimal KVM Hypervisor | ioctl API, CPU State, Real Mode vs Protected Mode | Medium |
| 42 | Slab Allocator | Object Caching, Memory Fragmentation, Buddy interaction | Medium |
| 43 | Process Migration (CRIU) | Checkpoint/Restore, Memory serialization, Register restoration | Medium |
| 44 | eBPF Verifier Logic | Control Flow Graph, Termination check, Safety verification | Medium |
| 45 | FUSE File System | User-Kernel Boundary, VFS operations, Context switching | Medium |
| 46 | Page Replacement (Clock/LRU) | Reference bits, Circular Queue, Cache Eviction | Medium |
| 47 | Interrupt Handler Simulator | Determinism, Hardware context, Work Queues | Medium |
| 48 | System Call Interceptor | Seccomp BPF, Attack Surface Reduction, Syscall Tables | Medium |
| 49 | Bootloader Logic | A20 Line, Segment Registers, 16-bit to 32-bit switch | Medium |
| 50 | Cgroup Resource Limiter | Accounting, Throttling, Resource Hierarchy | Medium |

### Module 9: Drivers & Hardware

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 51 | Virtio Ring Driver | Ring Buffers, Producer/Consumer, Descriptor Chains | Medium |
| 52 | DMA Controller Sim | Physical Addresses, Bus Mastering, Interrupts upon completion | Medium |
| 53 | Cache Coherency (MESI) | State Machines, Bus Snooping, Write-Back vs Write-Through | Medium |
| 54 | Soft Rasterizer (GPU) | Graphics Pipeline, Framebuffer, SIMD Basics | Medium |
| 55 | Memory Mapped Registers | Volatile keyword, Bit manipulation, Hardware registers | Medium |
| 56 | Watchdog Timer | Timeouts, System Reliability, Heartbeats | Medium |
| 57 | I2C Bit-Banging | Protocol Timing, Open-Drain lines, ACK/NACK | Medium |
| 58 | PCIe Enumeration | Depth-First Search, Address Space Layout, Header Type 0/1 | Medium |
| 59 | Rotary Encoder Decoder | Gray Code, State Transitions, Debouncing | Medium |
| 60 | Flash Translation Layer | Wear Leveling, Garbage Collection, Out-of-place updates | Medium |

### Module 10: HPC & Optimization

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 61 | SIMD Matrix Mul (AVX2) | Data Parallelism, Vendor Intrinsics, Alignment | Hard |
| 62 | False Sharing Demo | L1 Cache Lines, Padding/Alignment, Multi-core scaling | Hard |
| 63 | Branchless Logic | Pipeline Stalls, Speculative Execution, Bitwise hacks | Hard |
| 64 | Software Prefetching | Memory Latency Hiding, Pointer Chasing, CPU Pipelines | Hard |
| 65 | Cache Blocking (Tiling) | Spatial Locality, Loop Interchange, Cache Miss Reduction | Hard |
| 66 | Lock-Free Ring (MPMC) | Memory Barriers, Atomic CAS, Head/Tail sequencing | Hard |
| 67 | Fast Inverse Square Root | IEEE 754 Representation, Newton's Method, Approximation | Hard |
| 68 | Bitmap Scanning (ffs) | Bit Manipulation, CTZ/CLZ instructions, Word-level parallelism | Hard |
| 69 | Memory Arena (Huge Pages) | TLB Efficiency, Page Tables, mmap flags | Hard |
| 70 | Strided Access Pattern | Memory Layout, Cache Lines, Spatial Locality | Hard |

### Module 11: Databases & Storage

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 71 | B+ Tree Implementation | Disk Pages, Key Ordering, Tree Balancing | Hard |
| 72 | WAL (Write Ahead Log) | Append-only I/O, Checkpointing, Replay Logic | Hard |
| 73 | Bloom Filter | Hashing, Bit Arrays, False Positive Rates | Hard |
| 74 | Columnar Storage (Parquet) | Compression, CPU Vectorization friendliness, Access Patterns | Hard |
| 75 | Slotted Page Layout | Fragmentation, Indirection Pointers, Page Headers | Hard |
| 76 | Buffer Pool Manager | Pinning/Unpinning, LRU/Clock Replacer, Dirty Flags | Hard |
| 77 | External Merge Sort | I/O minimization, Streaming, File Handles | Hard |
| 78 | Bitcask (Key-Value) | Indexing, Sequential Writes, Compaction | Hard |
| 79 | MVCC (Snapshot Isolation) | Timestamps, Version Chains, Visibility Rules | Hard |
| 80 | Query Optimizer (Cost) | Table Statistics, Selectivity Estimation, Plan Selection | Hard |

### Module 12: Networked Systems

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 81 | HyperLogLog | Probabilistic counting, Hashing, LogLog averaging | Hard |
| 82 | Leaky Bucket Rate Limiter | Flow Control, Time verification, Queueing | Hard |
| 83 | Distributed ID Generator | Bit packing, Clock synchronization, Unique IDs | Hard |
| 84 | Geo-Replication Latency | Network partitions, CAP Theorem trade-offs, Latency | Hard |
| 85 | MapReduce (Shuffle) | Partitioning, Network I/O, Sorting efficiency | Hard |
| 86 | Streaming Window (Count) | Approximate computing, Stream processing, Frequency tracking | Hard |
| 87 | Merkle Tree | Cryptographic Hashing, Tree traversal, Difference detection | Hard |
| 88 | Distributed Lock (Redis) | Leases, Clock Drift, Fencing Tokens | Hard |
| 89 | Consistent Hash Ring (VNode) | Variance reduction, Key distribution, Rehashing | Hard |
| 90 | Circuit Breaker | Failure counting, State Transitions (Open/Closed/Half), Recovery | Hard |

### Module 13: AI Infrastructure

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 91 | Tensor Quantization (Int8) | Precision reduction, Scaling factors, Zero-points | Expert |
| 92 | Vector Search (HNSW) | Graph Navigation, Distance Metrics (Cosine/L2), Greedy Search | Expert |
| 93 | Attention Mechanism (Softmax) | Matrix Math, Softmax normalization, Scaling | Expert |
| 94 | Token Bucket (GenAI) | Token counting, Refill rates, Bursts | Expert |
| 95 | Parameter Sharding | Distributed Matrix Mul, Communication Overhead, Synchronization | Expert |
| 96 | KV Cache Manager | Memory Allocation, Paged Attention (vLLM style), Fragmentation | Expert |
| 97 | Logits Sampling | Probability distributions, Sorting, Cumulative Sum | Expert |
| 98 | Embedding Table Lookup | Memory access patterns, Sparse data, Indexing | Expert |
| 99 | Ring All-Reduce | Distributed Training, Bandwidth usage, Pipelining | Expert |
| 100 | Prompt Template Engine | String processing, Zero-copy, Memory pools | Expert |

### Module 14: Capstone

| # | Problem | Concept | Difficulty |
|---|---|---|---|
| 101 | Build Your Own Shell | fork/exec, Pipes, Signal Handling, Job Control | Expert |

---

# Part II: Embedded Software & RTOS 101

> **[View Full Detailed Roadmap Here](embedded_software_roadmap.md)**

## Module 1: Bare Metal Essentials
| # | Problem | Description |
|---|---|---|
| E01 | **[C Runtime Initialization (CRT0)](embedded_01_crt0.md)** | Initialize .bss/.data segments before main(). |
| E02 | **Linker Script Basics** | Place code in Flash and data in RAM. |
| E03 | **Memory Map Layout** | Define stack, heap, and shared memory regions. |
| E04 | **Register Bit Manipulation** | Type-safe register abstraction (volatile/bit-fields). |
| E05 | **Inline Assembly** | Use `NOP`, `WFI`, or specialized instructions. |
| E09 | **Function ABI Parser** | Manual stack frame parsing. |
| E10 | **Vector Table Setup** | Interrupt vector table relocation. |

## Module 2: Driver Development
| # | Problem | Description |
|---|---|---|
| E11 | **GPIO Driver** | Generic input/output driver. |
| E12 | **UART Polling** | Blocking serial transmission. |
| E13 | **UART Ring Buffer** | Interrupt-based circular buffer. |
| E17 | **I2C Bit-Banging** | Software implementation of I2C. |
| E21 | **ADC DMA Transfer** | Direct Memory Access for sensor data. |

## Module 3 & 4: RTOS & Concurrency
| # | Problem | Description |
|---|---|---|
| E26 | **Cooperative Scheduler** | simple run-to-completion scheduler. |
| E29 | **Context Switch** | Save/Restore CPU registers (Assembly). |
| E44 | **[Reentrancy Lab (The Gauntlet)](embedded_reentrancy_lab.md)** | Fix race conditions in a driver under preemption. |
| E45 | **Critical Sections** | `ENTER_CRITICAL` / `EXIT_CRITICAL`. |
| E52 | **IPC Ring Buffer** | Lock-free communication between cores. |

... *Refer to full roadmap for problems E46-E101*

## Module 10: Special Topic - SmartNIC & High Performance I/O
| # | Problem | Description |
|---|---|---|
| 102 | **PCIe Enumeration** | Scan PCI bus and map BARs. |
| 103 | **[SmartNIC Initialization](embedded_smartnic_init.md)** | Admin Queue / Mailbox handshake. |
| 104 | **Ring Doorbell** | MMIO producer index updates. |
| 105 | **Descriptor Chains** | Scatter-gather DMA descriptors. |
| 106 | **Interrupt Moderation** | NAPI-style polling/interrupt hybrid. |

