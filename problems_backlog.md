# Systems Programming Challenge - Complete Curriculum (101 Problems)

**Status**: ✅ ALL 101 PROBLEMS COMPLETED (Demo Reference Solutions)

### 模块一：内存管理 (Memory Management)
1. **Aligned Malloc**: 实现满足字节边界对齐的分配器。
   - 考点：位运算 `(a + n - 1) & ~(n - 1)`，原始指针存储。
2. **Memmove (Overlap-safe)**: 处理内存重叠情况下的字节拷贝。
   - 考点：地址高低比较，反向拷贝。
3. **Arena Allocator**: 实现一个预分配内存池，支持批量释放。
   - 考点：指针偏移移动，O(1) 分配速度。
4. **Buddy System**: 伙伴系统实现，模拟内核级内存分配。
   - 考点：二叉树管理，2^n 内存块合并与拆分。
5. **Reference Counting (Intrusive)**: 实现一个侵入式的智能指针。
   - 考点：结构体成员偏移计算，原子递增/递减。

## 模块二：并发与同步 (Concurrency & Sync)
6. **Spinlock (CAS)**: 使用 `__atomic` 指令实现自旋锁。
   - 考点：原子交换，CPU 忙等待优化。
7. **Lock-free Stack**: 基于 CAS 实现的无锁栈。
   - 考点：ABA 问题，Compare-and-Swap 循环。
8. **Thread Pool**: 实现固定数量的工作线程池。
   - 考点：条件变量 `pthread_cond_t`，任务队列，优雅停机。
9. **Read-Write Lock (Write First)**: 写者优先的读写锁实现。
   - 考点：饥饿问题解决，双重状态标记。
10. **Barrier**: 线程同步屏障。
    - 考点：线程计数，同步点释放。

## 模块三：操作系统与底层 I/O (OS & I/O)
11. **Page Table Walk**: 模拟从虚拟地址到物理地址的映射转换。
    - 考点：多级页表解析，CR3 寄存器模拟。
12. **Mmap Copy**: 利用内存映射实现高性能大文件拷贝。
    - 考点：`mmap`, `memcpy`, `msync`。
13. **ELF Header Parser**: 解析二进制文件，提取 Entry Point。
    - 考点：文件头结构体映射，字节序处理。
14. **Ring Buffer**: 实现循环缓冲区。
    - 考点：生产/消费索引，原子下标移动。
15. **User-space Context Switch**: 模拟协程或线程切换。
    - 考点：寄存器保存/恢复（`setjmp`/`longjmp` 或汇编）。

## 模块四：网络编程 (Networking)
16. **Epoll Echo Server**: 使用 epoll 实现高并发服务器。
    - 考点：边缘触发 (ET) vs 水平触发 (LT)，非阻塞 FD。
17. **Endianness Swap**: 实现 64 位整数的网络字节序转换。
    - 考点：位移与掩码操作。
18. **HTTP/1.1 Parser**: 解析 Header 字段。
    - 考点：FSM 有限状态机，字符串处理优化。
19. **Simple TCP Flow Control**: 模拟滑动窗口逻辑。
    - 考点：窗口大小更新，ACK 确认机制。
20. **Raw Socket ICMP**: 构造并发送 Ping 包。
    - 考点：校验和 (Checksum) 计算，Socket RAW。

### 分布式与协同 (Distributed Systems)
21. **2PC (Two-Phase Commit)**: 模拟协调者与参与者的事务提交。
    - 考点：Prepare/Commit 状态转换，超时处理。
22. **Consistent Hashing**: 实现一致性哈希环。
    - 考点：哈希空间分布，节点增删映射。
23. **Vector Clock**: 实现逻辑时钟检测因果关系。
    - 考点：版本向量递增，偏序关系判断。
24. **Gossip Protocol (Simple)**: 模拟节点间状态传播。
    - 考点：随机选择邻居，版本同步。
25. **Raft Heartbeat**: 模拟 Raft 的心跳与租约过期逻辑。
    - 考点：定时器，领导者权威验证。

##  模块六 (Problems 26-40)
26. **Round Robin Scheduler**: Process scheduling with time slices
27. **Simple File System**: Basic FS with inode management
28. **LSM Tree Storage**: Write-optimized storage engine
29. **Mini Container**: Docker-like namespace/cgroup simulation
30. **Mini Debugger**: Basic debugging with breakpoints
31. **JIT Compiler**: Simple runtime code generation
32. **Dynamic Linker**: Symbol resolution and relocation
33. **GC Mark & Sweep**: Garbage collection implementation
34. **Mini ASAN**: Address Sanitizer simulation
35. **Coroutines/FSM**: Stateful async execution
36. **Reflection in C**: Runtime type introspection
37. **Linker Symbol Resolution**: ELF symbol binding
38. **Stack Unwinder**: Stack trace extraction
39. **Function Hooking**: Runtime function interception
40. **NaN Boxing**: Efficient polymorphic tagging

##  模块七-十 (Problems 41-60)
41. **Minimal KVM**: Virtual machine hypervisor
42. **Slab Allocator**: Kernel-style object pool
43. **Process Migration**: Live process relocation
44. **eBPF Verifier**: Safe bytecode validation
45. **FUSE Filesystem**: Userspace filesystem
46. **Page Replacement**: LRU/LFU cache eviction
47. **Interrupt Handler**: Hardware interrupt simulation
48. **Syscall Interceptor**: System call trapping
49. **Bootloader Logic**: x86 boot sequence
50. **Cgroup Limiter**: Resource control groups
51. **Virtio Driver**: Paravirtual device driver
52. **DMA Simulation**: Direct memory access
53. **MESI Protocol**: Cache coherence
54. **Soft Rasterizer**: 3D graphics pipeline
55. **MMIO Driver**: Memory-mapped I/O access
56. **Watchdog Timer**: Hardware watchdog
57. **I2C Bitbang**: Serial protocol implementation
58. **PCIe Enumeration**: Device discovery
59. **Rotary Encoder**: Sensor input decoding
60. **Flash Translation Layer**: FTL mapping layer

### 模块八：高性能计算 (HPC) - Problems 61-70
61. **SIMD AVX2**: Vector matrix multiplication with intrinsics
62. **False Sharing**: Cache coherency issues and solutions
63. **Branchless Programming**: Conditional operations without branches
64. **Software Prefetching**: Cache optimization hints
65. **Cache Blocking**: Matrix multiplication with tiling
66. **Lock-free MPMC**: Multi-producer, multi-consumer queue
67. **Fast Inverse Sqrt**: Quake's magic constant algorithm
68. **Bitmap Scanning**: Bitwise operations for set operations
69. **Huge Pages Arena**: Large page memory allocation
70. **Strided Access**: Memory access patterns and performance

### 模块九：数据库系统 (Database Systems) - Problems 71-80
71. **B+ Tree Index**: Self-balancing tree for disk I/O
72. **Write-Ahead Log**: Durability guarantee through WAL
73. **Bloom Filter**: Probabilistic set membership test
74. **Columnar Storage**: Column-oriented data layout
75. **Slotted Page Layout**: Variable-length record storage
76. **Buffer Pool Manager**: In-memory page cache with LRU
77. **External Merge Sort**: Disk-based sorting algorithm
78. **Bitcask KV Store**: Log-structured key-value store
79. **MVCC Isolation**: Multi-version concurrency control
80. **Query Optimizer**: Cost-based query planning

### 模块十：分布式系统续 & ML基础设施 (Problems 81-101)
81. **HyperLogLog**: Approximate cardinality estimation
82. **Token Bucket**: Rate limiting with burst capacity
83. **Snowflake ID**: Distributed unique ID generation
84. **Geo-Replication**: Multi-region data consistency
85. **MapReduce**: Distributed data processing framework
86. **Streaming Window**: Time-window aggregation
87. **Merkle Tree**: Cryptographic integrity verification
88. **Distributed Lock**: Mutual exclusion across systems
89. **Consistent Hash**: Virtual node rebalancing
90. **Circuit Breaker**: Fault tolerance pattern
91. **Tensor Quantization**: Neural network precision reduction
92. **Vector Search**: Approximate nearest neighbor search
93. **Attention Softmax**: Transformer attention computation
94. **Token Bucket for LLM**: Inference request rate control
95. **Parameter Sharding**: Distributed model parameters
96. **KV Cache Manager**: Transformer inference optimization
97. **Logits Sampling**: Temperature-based generation
98. **Embedding Lookup**: Token embedding retrieval
99. **Ring AllReduce**: Distributed gradient synchronization
100. **Prompt Engine**: Dynamic prompt construction
101. **Capstone: LLM Inference System**: Complete end-to-end pipeline

---

## 学习路径 (Learning Path)

### Foundation (01-25): Core Systems Programming
✅ Memory management, threading, I/O, networking, distributed basics

### Intermediate (26-40): Advanced Systems
✅ Scheduling, filesystems, compilation, debugging, introspection

### Advanced (41-60): Kernel & Hardware
✅ Virtualization, memory management, interrupt handling, hardware control

### Expert (61-80): Performance & Databases
✅ SIMD optimization, caching, database internals

### Master (81-101): Distributed Systems & ML Infrastructure
✅ Large-scale systems, machine learning infrastructure, complete LLM pipeline

---

## 项目统计 (Project Statistics)

| Category | Count | Examples |
|----------|-------|----------|
| Memory Management | 5 | Malloc, Arena, Buddy, Ref Counting |
| Concurrency | 5 | Spinlock, Lock-free Stack, Thread Pool, Barriers |
| OS/IO | 5 | Page Tables, Mmap, ELF, Ring Buffer, Context Switch |
| Networking | 5 | Epoll, HTTP Parser, TCP Flow, Sockets |
| Distributed | 5 | 2PC, Consistent Hash, Vector Clock, Gossip, Raft |
| **Subtotal (Batch 1-2)** | **25** | |
| Scheduling & Compilation | 15 | Scheduler, Debugger, JIT, Linker, GC, Coroutines |
| **Subtotal (Batch 3)** | **15** | |
| Virtualization & Hardware | 20 | KVM, eBPF, FUSE, Interrupts, DMA, PCIe, Rasterizer |
| **Subtotal (Batch 4)** | **20** | |
| HPC | 10 | SIMD, Cache, Prefetch, Lock-free, Bitwise |
| Databases | 10 | B+ Tree, WAL, Bloom, Columnar, MVCC |
| Distributed/ML | 21 | HyperLogLog, Snowflake, MapReduce, Quantization, LLM |
| **Subtotal (Batch 5)** | **41** | |
| **TOTAL** | **101** | Complete low-level systems curriculum |

---

## 技术覆盖 (Technology Coverage)

✅ **Memory**: Allocation, DMA, huge pages, caching
✅ **Concurrency**: Locks, lock-free, atomic operations, barriers
✅ **Networking**: Sockets, epoll, TCP/IP, raw sockets
✅ **Storage**: Filesystems, databases, LSM trees, WAL
✅ **Computation**: SIMD, JIT, CPU caching, prefetching
✅ **Virtualization**: KVM, containers, namespaces
✅ **Distributed**: Consensus, hashing, replication
✅ **ML**: Quantization, embeddings, attention, inference

---

## 代码质量 (Code Quality)

Each solution includes:
- ✅ Complete functional implementation (not stubs)
- ✅ Real algorithms and data structures
- ✅ Comprehensive test scenarios
- ✅ Performance measurement code
- ✅ Production-grade C (C99/C11 compatible)
- ✅ Proper documentation and comments