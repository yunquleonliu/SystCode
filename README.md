# LowLevelMaster 🛠️

**"LeetCode for Systems Programming"**

Welcome to **LowLevelMaster**, a curated collection of systems programming challenges designed to bridge the gap between theory and real-world implementation. This repository contains 25 core problems covering Memory Management, Concurrency, OS Internals, Networking, and Distributed Systems.

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
| 1 | **[Aligned Malloc](problems/01_aligned_malloc)** | Implement an allocator with custom alignment support. | Bitwise Ops, Pointer Arithmetic | ✅ |
| 2 | **[Memmove](problems/02_memmove_overlap_safe)** | Safe memory copy handling overlapping regions. | Address Comparison, Reverse Copy | ⬜ |
| 3 | **[Arena Allocator](problems/03_arena_allocator)** | Fixed-size memory pool with batch freeing. | Pointer Bump, O(1) Allocation | ⬜ |
| 4 | **[Buddy System](problems/04_buddy_system)** | Kernel-style allocator for power-of-2 blocks. | Binary Trees, Block Merging/Splitting | ⬜ |
| 5 | **[Intrusive Ref Counting](problems/05_reference_counting_intrusive)** | Smart pointer implementation embedded in data. | `offsetof`, Atomic Inc/Dec | ⬜ |

### Module 2: Concurrency & Sync (并发与同步)
Build synchronization primitives from scratch using atomics.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 6 | **[Spinlock (CAS)](problems/06_spinlock_cas)** | User-space spinlock using atomic exchange. | `__atomic`, Busy-Wait Optimization | ⬜ |
| 7 | **[Lock-free Stack](problems/07_lock_free_stack)** | Thread-safe stack without mutexes. | ABA Problem, CAS Loops | ⬜ |
| 8 | **[Thread Pool](problems/08_thread_pool)** | Fixed-size worker pool for task execution. | Condition Variables, Task Queues | ⬜ |
| 9 | **[Read-Write Lock](problems/09_read_write_lock)** | Implement a writer-preferred RW lock. | Starvation Prevention, State Flags | ⬜ |
| 10 | **[Barrier](problems/10_barrier)** | Thread synchronization barrier. | Thread Counting, Release Points | ⬜ |

### Module 3: OS & Low-Level I/O (操作系统与底层 I/O)
Simulate core OS components and file operations.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 11 | **[Page Table Walk](problems/11_page_table_walk)** | Simulate virtual to physical address translation. | Multi-level Pages, MMU Simulation | ⬜ |
| 12 | **[Mmap Copy](problems/12_mmap_copy)** | High-perf file copy using memory mapping. | `mmap`, `msync`, Page Faults | ⬜ |
| 13 | **[ELF Parser](problems/13_elf_header_parser)** | Parse binary headers to find entry points. | Struct Mapping, Endianness | ⬜ |
| 14 | **[Ring Buffer](problems/14_ring_buffer)** | Lock-free circular buffer for IPC/Audio. | Producer/Consumer Indices, Modulo | ⬜ |
| 15 | **[User Context Switch](problems/15_user_space_context_switch)** | Simulate coroutine context switching. | `setjmp`/`longjmp`, Register Save/Restore | ⬜ |

### Module 4: Networking (网络编程)
Implement foundational network protocols and servers.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 16 | **[Epoll Echo Server](problems/16_epoll_echo_server)** | High-concurrency event-driven server. | ET vs LT, Non-blocking I/O | ⬜ |
| 17 | **[Endianness Swap](problems/17_endianness_swap)** | Network byte order conversion for 64-bit ints. | Bit Shifts, Masking | ⬜ |
| 18 | **[HTTP/1.1 Parser](problems/18_http_parser)** | Zero-copy HTTP header parsing. | FSM, String Optimization | ⬜ |
| 19 | **[TCP Flow Control](problems/19_simple_tcp_flow_control)** | Simulate sliding window protocol. | Window Updates, ACKs | ⬜ |
| 20 | **[Raw Socket ICMP](problems/20_raw_socket_icmp)** | Construct and send Ping packets manually. | Checksums, Raw Sockets | ⬜ |

### Module 5: Distributed Systems (分布式与协同)
Understand the algorithms that power cloud infrastructure.

| # | Problem | Description | Key Concepts | Status |
|---|---------|-------------|--------------|:---:|
| 21 | **[2PC (Two-Phase Commit)](problems/21_two_phase_commit)** | Distributed transaction coordinator simulation. | Prepare/Commit Phases, Timeouts | ⬜ |
| 22 | **[Consistent Hashing](problems/22_consistent_hashing)** | Distributed cache node mapping. | Hash Ring, Virtual Nodes | ⬜ |
| 23 | **[Vector Clock](problems/23_vector_clock)** | Causality tracking in distributed events. | Version Vectors, Partial Ordering | ⬜ |
| 24 | **[Gossip Protocol](problems/24_gossip_protocol)** | Epidemic status propagation. | Randomized Fanout, Convergence | ⬜ |
| 25 | **[Raft Heartbeat](problems/25_raft_heartbeat)** | Leader election heartbeat mechanism. | Timers, Lease Management | ⬜ |

---

## 🔮 Future Expansions
- **Compilers**: LLVM IR generation, Regex Engine.
- **Security**: Stack Overflow simulation, Crypto implementation.
- **Database**: B-Tree indices, LSM-Tree Log compaction, WAL.

---
*Happy Coding!*
