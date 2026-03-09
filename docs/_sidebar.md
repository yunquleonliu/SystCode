- **Core**
  - [Home](README.md)

- **Module 1: Memory**
  - [01 Aligned Malloc](01_aligned_malloc.md)
  - [02 Memmove](02_memmove_overlap_safe.md)
  - [03 Arena Allocator](03_arena_allocator.md)
  - [04 Buddy System](04_buddy_system.md)
  - [05 Ref Counting](05_reference_counting_intrusive.md)

- **Module 2: Concurrency**
  - [06 Spinlock](06_spinlock_cas.md)
  - [07 Lock-free Stack](07_lock_free_stack.md)
  - [08 Thread Pool](08_thread_pool.md)
  - [09 RW Lock](09_read_write_lock.md)
  - [10 Barrier](10_barrier.md)

- **Module 3: OS Internals**
  - [11 Page Table](11_page_table_walk.md)
  - [12 Mmap Copy](12_mmap_copy.md)
  - [13 ELF Parser](13_elf_header_parser.md)
  - [14 Ring Buffer](14_ring_buffer.md)
  - [15 Context Switch](15_user_space_context_switch.md)

- **Module 4: Networking**
  - [16 Epoll Server](16_epoll_echo_server.md)
  - [17 Endianness](17_endianness_swap.md)
  - [18 HTTP Parser](18_http_parser.md)
  - [19 TCP Flow](19_simple_tcp_flow_control.md)
  - [20 Raw Socket](20_raw_socket_icmp.md)

- **Module 5: Distributed**
  - [21 2PC](21_two_phase_commit.md)
  - [22 Consistent Hash](22_consistent_hashing.md)
  - [23 Vector Clock](23_vector_clock.md)
  - [24 Gossip](24_gossip_protocol.md)
  - [25 Raft Heartbeat](25_raft_heartbeat.md)

- **Module 6: Advanced OS**
  - [26 Round-Robin](26_round_robin_scheduler.md)
  - [27 Simple FS](27_simple_file_system.md)
  - [28 LSM Tree](28_lsm_tree_storage.md)
  - [29 Mini Container](29_mini_container.md)
  - [30 Mini Debugger](30_mini_debugger.md)

* Module 7: Compiler & Runtime
  * [31. JIT Compiler (x64)](31_jit_compiler.md)
  * [32. Custom Dynamic Linker](32_dynamic_linker.md)
  * [33. Mark & Sweep GC](33_gc_mark_sweep.md)
  * [34. Address Sanitizer (Mini-ASan)](34_mini_asan.md)
  * [35. Coroutines (State Machine)](35_coroutines_fsm.md)
  * [36. Reflection in C](36_reflection_c.md)
  * [37. Linker Symbol Resolution](37_linker_symbol_resolution.md)
  * [38. Stack Unwinder](38_stack_unwinder.md)
  * [39. Function Hooking (Trampoline)](39_function_hooking.md)
  * [40. NaN Boxing](40_nan_boxing.md)

* Module 8: Kernel & Virtualization
  * [41. Minimal KVM Hypervisor](41_minimal_kvm.md)
  * [42. Slab Allocator](42_slab_allocator.md)
  * [43. Process Migration (CRIU)](43_process_migration.md)
  * [44. eBPF Verifier Logic](44_ebpf_verifier.md)
  * [45. FUSE File System](45_fuse_filesystem.md)
  * [46. Page Replacement (Clock/LRU)](46_page_replacement.md)
  * [47. Interrupt Handler Simulator](47_interrupt_handler.md)
  * [48. System Call Interceptor](48_syscall_interceptor.md)
  * [49. Bootloader Logic](49_bootloader_logic.md)
  * [50. Cgroup Resource Limiter](50_cgroup_limiter.md)

* Module 9: Drivers & Hardware
  * [51. Virtio Ring Driver](51_virtio_driver.md)
  * [52. DMA Controller Sim](52_dma_sim.md)
  * [53. Cache Coherency (MESI)](53_mesi_protocol.md)
  * [54. Soft Rasterizer (GPU)](54_soft_rasterizer.md)
  * [55. Memory Mapped Registers](55_mmio_driver.md)
  * [56. Watchdog Timer](56_watchdog_timer.md)
  * [57. I2C Bit-Banging](57_i2c_bitbang.md)
  * [58. PCIe Enumeration](58_pcie_enumeration.md)
  * [59. Rotary Encoder Decoder](59_rotary_encoder.md)
  * [60. Flash Translation Layer](60_flash_translation.md)

* Module 10: HPC & Optimization
  * [61. SIMD Matrix Mul (AVX2)](61_simd_avx2.md)
  * [62. False Sharing Demo](62_false_sharing.md)
  * [63. Branchless Logic](63_branchless_programming.md)
  * [64. Software Prefetching](64_software_prefetching.md)
  * [65. Cache Blocking (Tiling)](65_cache_blocking.md)
  * [66. Lock-Free Ring (MPMC)](66_lock_free_mpmc.md)
  * [67. Fast Inverse Square Root](67_fast_inv_sqrt.md)
  * [68. Bitmap Scanning (ffs)](68_bitmap_scanning.md)
  * [69. Memory Arena (Huge Pages)](69_huge_pages_arena.md)
  * [70. Strided Access Pattern](70_strided_access.md)

* Module 11: Databases & Storage
  * [71. B+ Tree Implementation](71_b_plus_tree.md)
  * [72. WAL (Write Ahead Log)](72_write_ahead_log.md)
  * [73. Bloom Filter](73_bloom_filter.md)
  * [74. Columnar Storage (Parquet)](74_columnar_storage.md)
  * [75. Slotted Page Layout](75_slotted_page.md)
  * [76. Buffer Pool Manager](76_buffer_pool.md)
  * [77. External Merge Sort](77_external_merge_sort.md)
  * [78. Bitcask (Key-Value)](78_bitcask_kv.md)
  * [79. MVCC (Snapshot Isolation)](79_mvcc_isolation.md)
  * [80. Query Optimizer (Cost)](80_query_optimizer.md)

* Module 12: Networked Systems
  * [81. HyperLogLog](81_hyperloglog.md)
  * [82. Leaky Bucket Rate Limiter](82_rate_limiter.md)
  * [83. Distributed ID Generator](83_snowflake_id.md)
  * [84. Geo-Replication Latency](84_geo_replication.md)
  * [85. MapReduce (Shuffle)](85_mapreduce_shuffle.md)
  * [86. Streaming Window (Count)](86_streaming_window.md)
  * [87. Merkle Tree](87_merkle_tree.md)
  * [88. Distributed Lock (Redis)](88_distributed_lock.md)
  * [89. Consistent Hash Ring (VNode)](89_consistent_hash_vnode.md)
  * [90. Circuit Breaker](90_circuit_breaker.md)

* Module 13: AI Infrastructure
  * [91. Tensor Quantization (Int8)](91_tensor_quantization.md)
  * [92. Vector Search (HNSW)](92_vector_search.md)
  * [93. Attention Mechanism (Softmax)](93_attention_softmax.md)
  * [94. Token Bucket (GenAI)](94_token_bucket_llm.md)
  * [95. Parameter Sharding](95_param_sharding.md)
  * [96. KV Cache Manager](96_kv_cache_manager.md)
  * [97. Logits Sampling](97_logits_sampling.md)
  * [98. Embedding Table Lookup](98_embedding_lookup.md)
  * [99. Ring All-Reduce](99_ring_all_reduce.md)
  * [100. Prompt Template Engine](100_prompt_engine.md)

* Module 14: Capstone
  * [101. Build Your Own Shell](101_capstone_shell.md)

- **Embedded Software 101 (Docs First)**
  - [Embedded Roadmap](embedded_software_roadmap.md)
  - [Embedded Specs Index](embedded_specs_index.md)
  - [Problem Spec Template](embedded_problem_template.md)
  - [E001 CRT0](embedded_01_crt0.md)
  - [E044 Reentrancy Lab](embedded_reentrancy_lab.md)
  - [E103 SmartNIC Initialization](embedded_smartnic_init.md)
