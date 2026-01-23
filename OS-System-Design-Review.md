# OS Level System Design Review

A comprehensive list of OS level system design topics for review and learning. This is a living document - contributions are welcome!

## Table of Contents
1. [Memory Management](#memory-management)
2. [Process Management](#process-management)
3. [File Systems](#file-systems)
4. [I/O Systems](#io-systems)
5. [Concurrency and Synchronization](#concurrency-and-synchronization)
6. [CPU Scheduling](#cpu-scheduling)
7. [Deadlocks](#deadlocks)
8. [Virtual Memory](#virtual-memory)
9. [Networking](#networking)
10. [Security](#security)
11. [Distributed Systems](#distributed-systems)
12. [Real-Time Systems](#real-time-systems)

---

## Memory Management

### Key Topics
- **Memory Hierarchy**: Cache, RAM, Virtual Memory, Disk
- **Memory Allocation Strategies**:
  - First Fit, Best Fit, Worst Fit
  - Buddy System
  - Slab Allocation
- **Paging and Segmentation**
- **Memory Protection and Access Control**
- **Garbage Collection**: Mark-and-Sweep, Reference Counting, Generational GC
- **Memory-Mapped Files**
- **Shared Memory**

### Questions to Consider
- How does the OS manage physical and virtual memory?
- What are the trade-offs between different allocation strategies?
- How does paging prevent fragmentation?
- What is a TLB (Translation Lookaside Buffer) and why is it important?

---

## Process Management

### Key Topics
- **Process vs Thread**
- **Process States**: New, Ready, Running, Waiting, Terminated
- **Process Control Block (PCB)**
- **Context Switching**
- **Inter-Process Communication (IPC)**:
  - Pipes, Message Queues
  - Shared Memory
  - Sockets
  - Signals
- **Process Creation and Termination**: fork(), exec(), wait(), exit()
- **Daemon Processes**
- **Zombie and Orphan Processes**

### Questions to Consider
- What is the difference between a process and a thread?
- How does the OS perform a context switch?
- What are the costs associated with process creation?
- When should you use threads vs processes?

---

## File Systems

### Key Topics
- **File System Architecture**: VFS, inode, directory structure
- **File Allocation Methods**:
  - Contiguous Allocation
  - Linked Allocation
  - Indexed Allocation
- **Directory Implementation**: Linear List, Hash Table
- **Free Space Management**: Bit Vector, Linked List, Grouping
- **File System Types**: ext2/3/4, NTFS, FAT, ZFS, Btrfs
- **Journaling File Systems**
- **RAID Levels**: RAID 0, 1, 5, 6, 10
- **File System Caching and Buffering**
- **File Locking Mechanisms**

### Questions to Consider
- How does journaling improve file system reliability?
- What are the trade-offs between different file allocation methods?
- How does an inode work in Unix/Linux file systems?
- What is the purpose of a virtual file system (VFS)?

---

## I/O Systems

### Key Topics
- **I/O Hardware**: Devices, Controllers, Buses
- **I/O Methods**:
  - Programmed I/O
  - Interrupt-Driven I/O
  - Direct Memory Access (DMA)
- **I/O Scheduling**:
  - FCFS, SSTF, SCAN, C-SCAN, LOOK
- **Buffering**: Single, Double, Circular
- **Device Drivers**
- **Asynchronous I/O**
- **I/O Protection**

### Questions to Consider
- What are the advantages of DMA over interrupt-driven I/O?
- How does the OS manage different types of I/O devices?
- What is the role of an I/O scheduler?
- How do device drivers interact with the kernel?

---

## Concurrency and Synchronization

### Key Topics
- **Race Conditions**
- **Critical Section Problem**
- **Synchronization Primitives**:
  - Mutex (Mutual Exclusion)
  - Semaphores (Binary, Counting)
  - Monitors
  - Condition Variables
  - Read-Write Locks
  - Spinlocks
- **Lock-Free Programming**: Atomic Operations, Compare-and-Swap (CAS)
- **Thread Pools**
- **Producer-Consumer Problem**
- **Readers-Writers Problem**
- **Dining Philosophers Problem**

### Questions to Consider
- What is the difference between a mutex and a semaphore?
- When should you use a spinlock vs a mutex?
- How do you prevent race conditions?
- What is priority inversion and how can it be solved?

---

## CPU Scheduling

### Key Topics
- **Scheduling Criteria**: CPU Utilization, Throughput, Turnaround Time, Waiting Time, Response Time
- **Scheduling Algorithms**:
  - First-Come, First-Served (FCFS)
  - Shortest Job First (SJF)
  - Priority Scheduling
  - Round Robin (RR)
  - Multilevel Queue Scheduling
  - Multilevel Feedback Queue Scheduling
- **Real-Time Scheduling**: Rate Monotonic, Earliest Deadline First
- **Multiprocessor Scheduling**: Load Balancing, Processor Affinity
- **Thread Scheduling**: User-Level vs Kernel-Level Threads

### Questions to Consider
- What is the convoy effect in FCFS scheduling?
- How does the time quantum affect Round Robin performance?
- What is CPU affinity and why is it important?
- How do you schedule real-time tasks?

---

## Deadlocks

### Key Topics
- **Deadlock Conditions**: Mutual Exclusion, Hold and Wait, No Preemption, Circular Wait
- **Deadlock Prevention**: Negate one of the four conditions
- **Deadlock Avoidance**: Banker's Algorithm, Resource Allocation Graph
- **Deadlock Detection and Recovery**
- **Livelock**
- **Starvation**

### Questions to Consider
- How does the Banker's Algorithm work?
- What are the trade-offs between deadlock prevention and avoidance?
- How can you break a deadlock once detected?
- What is the difference between deadlock and livelock?

---

## Virtual Memory

### Key Topics
- **Demand Paging**
- **Page Replacement Algorithms**:
  - FIFO (First-In-First-Out)
  - Optimal Page Replacement
  - Least Recently Used (LRU)
  - LRU Approximation (Clock Algorithm)
  - Counting-Based: LFU, MFU
- **Thrashing**: Causes and Solutions
- **Working Set Model**
- **Page Fault Handling**
- **Translation Lookaside Buffer (TLB)**
- **Inverted Page Tables**
- **Memory-Mapped I/O**

### Questions to Consider
- What is a page fault and how does the OS handle it?
- Why does thrashing occur and how can it be prevented?
- What is the working set model?
- How does the TLB improve performance?

---

## Networking

### Key Topics
- **Network Stack**: OSI Model, TCP/IP Model
- **Socket Programming**: TCP Sockets, UDP Sockets
- **Network Protocols**: TCP, UDP, HTTP, DNS
- **Network File Systems**: NFS, SMB/CIFS
- **Network Security**: Firewalls, VPNs, SSL/TLS
- **Quality of Service (QoS)**
- **Load Balancing**
- **Network Performance**: Latency, Bandwidth, Throughput

### Questions to Consider
- What is the difference between TCP and UDP?
- How does the three-way handshake work in TCP?
- What is a socket and how is it used in networking?
- How do network file systems work?

---

## Security

### Key Topics
- **Authentication and Authorization**
- **Access Control**: DAC, MAC, RBAC
- **Security Models**: Bell-LaPadula, Biba
- **Cryptography**: Symmetric, Asymmetric, Hashing
- **Buffer Overflow Attacks**
- **Return-Oriented Programming (ROP)**
- **Address Space Layout Randomization (ASLR)**
- **Data Execution Prevention (DEP)**
- **Sandboxing and Isolation**
- **Principle of Least Privilege**
- **Security Auditing and Logging**

### Questions to Consider
- What is the difference between authentication and authorization?
- How does ASLR protect against attacks?
- What are the different access control models?
- How do you prevent buffer overflow attacks?

---

## Distributed Systems

### Key Topics
- **Distributed System Models**: Client-Server, Peer-to-Peer
- **Clock Synchronization**: Lamport Clocks, Vector Clocks
- **Distributed Mutual Exclusion**
- **Consensus Algorithms**: Paxos, Raft
- **Distributed File Systems**: HDFS, GFS
- **Replication and Consistency**: Strong, Eventual, Causal Consistency
- **CAP Theorem**: Consistency, Availability, Partition Tolerance
- **Distributed Transactions**: Two-Phase Commit, Three-Phase Commit
- **Message Passing and RPC**
- **Fault Tolerance and Recovery**

### Questions to Consider
- What is the CAP theorem and what are its implications?
- How do consensus algorithms ensure consistency?
- What is the difference between strong and eventual consistency?
- How do distributed systems handle failures?

---

## Real-Time Systems

### Key Topics
- **Real-Time Constraints**: Hard, Soft, Firm Deadlines
- **Real-Time Scheduling**:
  - Rate Monotonic Scheduling (RMS)
  - Earliest Deadline First (EDF)
  - Deadline Monotonic Scheduling
- **Priority Inversion**: Priority Inheritance, Priority Ceiling
- **Real-Time Operating Systems (RTOS)**: VxWorks, FreeRTOS, QNX
- **Interrupt Latency**
- **Jitter**
- **Resource Reservation**

### Questions to Consider
- What is the difference between hard and soft real-time systems?
- How does Rate Monotonic Scheduling work?
- What is priority inversion and how can it be mitigated?
- What are the characteristics of an RTOS?

---

## Contributing

This is a living document and contributions are welcome! Please feel free to:
- Add new topics or subtopics
- Expand on existing content
- Add practical examples or code snippets
- Suggest relevant resources and references
- Correct errors or improve clarity

To contribute:
1. Fork this repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request with a clear description of your additions

---

## Additional Resources

### Books
- "Operating System Concepts" by Silberschatz, Galvin, and Gagne
- "Modern Operating Systems" by Andrew S. Tanenbaum
- "The Design of the UNIX Operating System" by Maurice J. Bach
- "Operating Systems: Three Easy Pieces" by Remzi and Andrea Arpaci-Dusseau

### Online Resources
- [OSDev Wiki](https://wiki.osdev.org/)
- [Linux Kernel Documentation](https://www.kernel.org/doc/html/latest/)
- [FreeBSD Handbook](https://docs.freebsd.org/en/books/handbook/)

### Practice
- Implement system calls and kernel modules
- Build a simple operating system (e.g., using [OS Tutorial](https://github.com/cfenollosa/os-tutorial))
- Solve OS-related problems on platforms like LeetCode, HackerRank

---

## License

Feel free to use this resource for learning and educational purposes.
