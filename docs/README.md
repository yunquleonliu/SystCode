# Q101 of Low Level System 🛠️

**"LeetCode for Systems Programming"**

A curated collection of **101 core systems programming challenges** covering Memory, Concurrency, OS Internals, Networking, Distributed Systems, AI Infra, and more.

## Getting Started
1. Click on a problem in the sidebar to view the challenge.
2. Clone the repo to start coding:
   ```bash
   git clone https://github.com/yunquleonliu/SystCode.git
   ```
3. Check the `problems/` directory for C templates.

## Curriculum Overview

### Module 1: Memory Management
- [01. Aligned Malloc](01_aligned_malloc.md) - _Bitwise Ops, Pointer Arithmetic_
- [02. Memmove](02_memmove_overlap_safe.md) - _Address Comparison, Reverse Copy_
- [03. Arena Allocator](03_arena_allocator.md) - _Pointer Bump, O(1) Allocation_
- [04. Buddy System](04_buddy_system.md) - _Binary Trees, Block Merging/Splitting_
- [05. Intrusive Ref Counting](05_reference_counting_intrusive.md) - _offsetof, Atomic Inc/Dec_

### Module 2: Concurrency & Sync
- [06. Spinlock (CAS)](06_spinlock_cas.md) - _\_\_atomic, Busy-Wait Optimization_
- [07. Lock-free Stack](07_lock_free_stack.md) - _ABA Problem, CAS Loops_
- [08. Thread Pool](08_thread_pool.md) - _Condition Variables, Task Queues_
- [09. Read-Write Lock](09_read_write_lock.md) - _Starvation Prevention, State Flags_
- [10. Barrier](10_barrier.md) - _Thread Counting, Release Points_

### Module 3: OS & Low-Level I/O
- [11. Page Table Walk](11_page_table_walk.md) - _Multi-level Pages, MMU Simulation_
- [12. Mmap Copy](12_mmap_copy.md) - _mmap, msync, Page Faults_
- [13. ELF Parser](13_elf_header_parser.md) - _Struct Mapping, Endianness_
- [14. Ring Buffer](14_ring_buffer.md) - _Producer/Consumer Indices, Modulo_
- [15. User Context Switch](15_user_space_context_switch.md) - _setjmp/longjmp, Register Save/Restore_

### Module 4: Networking
- [16. Epoll Echo Server](16_epoll_echo_server.md) - _ET vs LT, Non-blocking I/O_
- [17. Endianness Swap](17_endianness_swap.md) - _Bit Shifts, Masking_
- [18. HTTP/1.1 Parser](18_http_parser.md) - _FSM, String Optimization_
- [19. TCP Flow Control](19_simple_tcp_flow_control.md) - _Window Updates, ACKs_
- [20. Raw Socket ICMP](20_raw_socket_icmp.md) - _Checksums, Raw Sockets_

### Module 5: Distributed Systems
- [21. 2PC (Two-Phase Commit)](21_two_phase_commit.md) - _Prepare/Commit Phases, Timeouts_
- [22. Consistent Hashing](22_consistent_hashing.md) - _Hash Ring, Virtual Nodes_
- [23. Vector Clock](23_vector_clock.md) - _Version Vectors, Partial Ordering_
- [24. Gossip Protocol](24_gossip_protocol.md) - _Randomized Fanout, Convergence_
- [25. Raft Heartbeat](25_raft_heartbeat.md) - _Timers, Lease Management_

### Module 6: Advanced OS Engineering
- [26. Round-Robin Scheduler](26_round_robin_scheduler.md) - _Preemption, Quantum, Task States_
- [27. Simple File System](27_simple_file_system.md) - _Inodes, Bitmaps, Superblock_
- [28. LSM-Tree](28_lsm_tree_storage.md) - _MemTable, SSTable, Write Amplification_
- [29. Mini Container](29_mini_container.md) - _clone, unshare, PID/Mount Namespace_
- [30. Mini Debugger](30_mini_debugger.md) - _ptrace, System Calls, Register Inspection_

### Module 7: Compiler & Runtime
- [31. JIT Compiler (x64)](31_jit_compiler.md) - _mmap PROT_EXEC, ABI calling convention, Instruction Encoding_
- [32. Custom Dynamic Linker](32_dynamic_linker.md) - _ELF Dynamic Section, Relocation, Lazy Binding_
- [33. Mark & Sweep GC](33_gc_mark_sweep.md) - _Stack scanning, Reachability Graph, Memory Reclamation_
- [34. Address Sanitizer (Mini-ASan)](34_mini_asan.md) - _Shadow Memory mapping, Poison values, Instrumentation_
- [35. Coroutines (State Machine)](35_coroutines_fsm.md) - _State Machines, Macro Expansion, Reentrancy_
- [36. Reflection in C](36_reflection_c.md) - _Preprocessor Metaprogramming, Offsetof, Type Traits_
- [37. Linker Symbol Resolution](37_linker_symbol_resolution.md) - _Symbol Tables, Weak/Strong definitions, Common blocks_
- [38. Stack Unwinder](38_stack_unwinder.md) - _Stack Frames, RBP Register, Return Addresses_
- [39. Function Hooking (Trampoline)](39_function_hooking.md) - _Code Patching, Relative Jumps, Instruction preservation_
- [40. NaN Boxing](40_nan_boxing.md) - _IEEE 754, Bitwise casting, Type Tagging_

### Module 8: Kernel & Virtualization
- [41. Minimal KVM Hypervisor](41_minimal_kvm.md) - _ioctl API, CPU State, Real Mode vs Protected Mode_
- [42. Slab Allocator](42_slab_allocator.md) - _Object Caching, Memory Fragmentation, Buddy interaction_
- [43. Process Migration (CRIU)](43_process_migration.md) - _Checkpoint/Restore, Memory serialization, Register restoration_
- [44. eBPF Verifier Logic](44_ebpf_verifier.md) - _Control Flow Graph, Termination check, Safety verification_
- [45. FUSE File System](45_fuse_filesystem.md) - _User-Kernel Boundary, VFS operations, Context switching_
- [46. Page Replacement (Clock/LRU)](46_page_replacement.md) - _Reference bits, Circular Queue, Cache Eviction_
- [47. Interrupt Handler Simulator](47_interrupt_handler.md) - _Determinism, Hardware context, Work Queues_
- [48. System Call Interceptor](48_syscall_interceptor.md) - _Seccomp BPF, Attack Surface Reduction, Syscall Tables_
- [49. Bootloader Logic](49_bootloader_logic.md) - _A20 Line, Segment Registers, 16-bit to 32-bit switch_
- [50. Cgroup Resource Limiter](50_cgroup_limiter.md) - _Accounting, Throttling, Resource Hierarchy_

### Module 9: Drivers & Hardware
- [51. Virtio Ring Driver](51_virtio_driver.md) - _Ring Buffers, Producer/Consumer, Descriptor Chains_
- [52. DMA Controller Sim](52_dma_sim.md) - _Physical Addresses, Bus Mastering, Interrupts upon completion_
- [53. Cache Coherency (MESI)](53_mesi_protocol.md) - _State Machines, Bus Snooping, Write-Back vs Write-Through_
- [54. Soft Rasterizer (GPU)](54_soft_rasterizer.md) - _Graphics Pipeline, Framebuffer, SIMD Basics_
- [55. Memory Mapped Registers](55_mmio_driver.md) - _Volatile keyword, Bit manipulation, Hardware registers_
- [56. Watchdog Timer](56_watchdog_timer.md) - _Timeouts, System Reliability, Heartbeats_
- [57. I2C Bit-Banging](57_i2c_bitbang.md) - _Protocol Timing, Open-Drain lines, ACK/NACK_
- [58. PCIe Enumeration](58_pcie_enumeration.md) - _Depth-First Search, Address Space Layout, Header Type 0/1_
- [59. Rotary Encoder Decoder](59_rotary_encoder.md) - _Gray Code, State Transitions, Debouncing_
- [60. Flash Translation Layer](60_flash_translation.md) - _Wear Leveling, Garbage Collection, Out-of-place updates_

### Module 10: HPC & Optimization
- [61. SIMD Matrix Mul (AVX2)](61_simd_avx2.md) - _Data Parallelism, Vendor Intrinsics, Alignment_
- [62. False Sharing Demo](62_false_sharing.md) - _L1 Cache Lines, Padding/Alignment, Multi-core scaling_
- [63. Branchless Logic](63_branchless_programming.md) - _Pipeline Stalls, Speculative Execution, Bitwise hacks_
- [64. Software Prefetching](64_software_prefetching.md) - _Memory Latency Hiding, Pointer Chasing, CPU Pipelines_
- [65. Cache Blocking (Tiling)](65_cache_blocking.md) - _Spatial Locality, Loop Interchange, Cache Miss Reduction_
- [66. Lock-Free Ring (MPMC)](66_lock_free_mpmc.md) - _Memory Barriers, Atomic CAS, Head/Tail sequencing_
- [67. Fast Inverse Square Root](67_fast_inv_sqrt.md) - _IEEE 754 Representation, Newton's Method, Approximation_
- [68. Bitmap Scanning (ffs)](68_bitmap_scanning.md) - _Bit Manipulation, CTZ/CLZ instructions, Word-level parallelism_
- [69. Memory Arena (Huge Pages)](69_huge_pages_arena.md) - _TLB Efficiency, Page Tables, mmap flags_
- [70. Strided Access Pattern](70_strided_access.md) - _Memory Layout, Cache Lines, Spatial Locality_

### Module 11: Databases & Storage
- [71. B+ Tree Implementation](71_b_plus_tree.md) - _Disk Pages, Key Ordering, Tree Balancing_
- [72. WAL (Write Ahead Log)](72_write_ahead_log.md) - _Append-only I/O, Checkpointing, Replay Logic_
- [73. Bloom Filter](73_bloom_filter.md) - _Hashing, Bit Arrays, False Positive Rates_
- [74. Columnar Storage (Parquet)](74_columnar_storage.md) - _Compression, CPU Vectorization friendliness, Access Patterns_
- [75. Slotted Page Layout](75_slotted_page.md) - _Fragmentation, Indirection Pointers, Page Headers_
- [76. Buffer Pool Manager](76_buffer_pool.md) - _Pinning/Unpinning, LRU/Clock Replacer, Dirty Flags_
- [77. External Merge Sort](77_external_merge_sort.md) - _I/O minimization, Streaming, File Handles_
- [78. Bitcask (Key-Value)](78_bitcask_kv.md) - _Indexing, Sequential Writes, Compaction_
- [79. MVCC (Snapshot Isolation)](79_mvcc_isolation.md) - _Timestamps, Version Chains, Visibility Rules_
- [80. Query Optimizer (Cost)](80_query_optimizer.md) - _Table Statistics, Selectivity Estimation, Plan Selection_

### Module 12: Networked Systems
- [81. HyperLogLog](81_hyperloglog.md) - _Probabilistic counting, Hashing, LogLog averaging_
- [82. Leaky Bucket Rate Limiter](82_rate_limiter.md) - _Flow Control, Time verification, Queueing_
- [83. Distributed ID Generator](83_snowflake_id.md) - _Bit packing, Clock synchronization, Unique IDs_
- [84. Geo-Replication Latency](84_geo_replication.md) - _Network partitions, CAP Theorem trade-offs, Latency_
- [85. MapReduce (Shuffle)](85_mapreduce_shuffle.md) - _Partitioning, Network I/O, Sorting efficiency_
- [86. Streaming Window (Count)](86_streaming_window.md) - _Approximate computing, Stream processing, Frequency tracking_
- [87. Merkle Tree](87_merkle_tree.md) - _Cryptographic Hashing, Tree traversal, Difference detection_
- [88. Distributed Lock (Redis)](88_distributed_lock.md) - _Leases, Clock Drift, Fencing Tokens_
- [89. Consistent Hash Ring (VNode)](89_consistent_hash_vnode.md) - _Variance reduction, Key distribution, Rehashing_
- [90. Circuit Breaker](90_circuit_breaker.md) - _Failure counting, State Transitions (Open/Closed/Half), Recovery_

### Module 13: AI Infrastructure
- [91. Tensor Quantization (Int8)](91_tensor_quantization.md) - _Precision reduction, Scaling factors, Zero-points_
- [92. Vector Search (HNSW)](92_vector_search.md) - _Graph Navigation, Distance Metrics (Cosine/L2), Greedy Search_
- [93. Attention Mechanism (Softmax)](93_attention_softmax.md) - _Matrix Math, Softmax normalization, Scaling_
- [94. Token Bucket (GenAI)](94_token_bucket_llm.md) - _Token counting, Refill rates, Bursts_
- [95. Parameter Sharding](95_param_sharding.md) - _Distributed Matrix Mul, Communication Overhead, Synchronization_
- [96. KV Cache Manager](96_kv_cache_manager.md) - _Memory Allocation, Paged Attention (vLLM style), Fragmentation_
- [97. Logits Sampling](97_logits_sampling.md) - _Probability distributions, Sorting, Cumulative Sum_
- [98. Embedding Table Lookup](98_embedding_lookup.md) - _Memory access patterns, Sparse data, Indexing_
- [99. Ring All-Reduce](99_ring_all_reduce.md) - _Distributed Training, Bandwidth usage, Pipelining_
- [100. Prompt Template Engine](100_prompt_engine.md) - _String processing, Zero-copy, Memory pools_

### Module 14: Capstone
- [101. Build Your Own Shell](101_capstone_shell.md) - _fork/exec, Pipes, Signal Handling, Job Control_
