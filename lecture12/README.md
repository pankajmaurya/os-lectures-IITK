Key Concepts
Threads vs Processes: A process can spawn multiple threads that share the same resources and virtual address space. Threads are the basic unit of CPU execution, each having their own CPU registers and execution state, while processes serve as containers for resources like address space, threads, and open files.
Multiple Processes vs Multiple Threads
Multiple Processes Advantages:

Better modularity since processes run in separate address spaces
Errors are less likely to propagate between processes
Processes interact only through well-defined interfaces

Multiple Threads Advantages:

Significantly better performance - thread operations are orders of magnitude faster
Thread creation is much quicker than process creation
Context switching between threads is cheaper since they share the same address space, resulting in fewer cache misses and TLB (Translation Look-aside Buffer) misses

Thread Implementation Approaches
1. Kernel-Level Threads:

Main disadvantage: All thread operations require system calls, creating substantial overhead
System call overhead is particularly problematic since thread operations should be fast

2. User-Level Threads:

Implemented by user-level libraries that manage threads without kernel involvement
The kernel sees only one thread per process; the library handles scheduling among user threads

Advantages:

Much faster since no system calls are needed
Allows application-specific scheduling policies

Disadvantages:

Cannot execute in parallel on multiple processors
If one thread blocks in the kernel, all threads in the process are blocked
Must avoid synchronous (blocking) system calls

3. Hybrid Approach:

Combines both kernel and user-level thread support
User-level library manages multiple user threads across fewer kernel threads
Provides better performance than pure kernel threads while avoiding some limitations of pure user threads

This lecture establishes the fundamental trade-offs between different threading models that operating systems must address.
