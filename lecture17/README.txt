This is Lecture 17 from an Operating Systems course (CS330) at IIT Kanpur, focusing on synchronization in multi-processor systems and interaction with interrupt handlers. Here's a summary of the key topics covered:
Preemptible Kernels and Synchronization
The lecture discusses how to ensure exclusive access to data structures in preemptible kernels (kernels that can be interrupted and context-switched). Unlike non-preemptible kernels, real-time applications require predictable response times, necessitating different synchronization approaches.
Solutions for general data structures:

Use semaphores or locks instead of disabling interrupts for the entire access duration
Only disable interrupts briefly during semaphore acquire/release operations
This allows better responsiveness while maintaining mutual exclusion

Interrupt Handler Synchronization Problems
Critical issue: Data structures accessed by both regular processes and interrupt handlers cannot use semaphores due to deadlock risk:

Process acquires semaphore for data structure D
Interrupt occurs during modification
Interrupt handler needs same semaphore but it's held by the interrupted process
Interrupt handler (running in interrupted process context) goes to sleep
Deadlock: process waits for semaphore it already holds

Solution: Must disable interrupts when accessing interrupt-shared data structures.
Multi-processor Synchronization
On multi-processor systems, disabling interrupts isn't sufficient since other processors can still access shared data simultaneously. This requires hardware-supported atomic operations.
Test-and-Set Instruction:

Atomically reads old value and sets memory location to 1
Used to implement spin-locks for mutual exclusion
Processes "spin" in a loop waiting for lock availability

Advanced Implementation Details
Spin-lock vs Semaphores:

Spin-locks preferred for very brief critical sections (less overhead than context switches)
Semaphores better for longer critical sections to avoid wasting CPU cycles

Lost Wakeup Problem:

Occurs when wakeup signal happens between unlocking and sleeping
Solution: Make unlocking and sleeping atomic by releasing lock just before calling scheduler

Multi-processor Interrupt Handling:

Requires both spin-locks AND interrupt disabling
Must repeatedly disable/restore interrupts while spinning to avoid delaying interrupt service

The lecture provides detailed code examples showing correct implementations of these synchronization primitives for both single and multi-processor systems.
