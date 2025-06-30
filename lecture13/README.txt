Thread APIs
POSIX Thread API (Pthreads): The lecture mentions this standard thread API but doesn't provide detailed implementation examples.
Java Thread API: Two methods for creating threads in Java:

Extend Thread class: Create a class that extends Thread, define a run() method, then create an instance and call start()
Implement Runnable interface: Create a class implementing Runnable, pass it to Thread constructor, then call start()

Key Java thread methods mentioned include currentThread() and join().
Process/Thread Synchronization
The lecture introduces synchronization problems through the Producer-Consumer Problem:

Scenario: Producer processes generate data for consumer processes to use
Buffer: Data stored in finite-size FIFO buffer
Real-world application: Server architecture where master process receives requests, worker processes handle them

Race Condition Problem
The lecture demonstrates a critical synchronization issue:
Problem: When producer and consumer both try to modify a shared count variable simultaneously, the assembly-level instructions can interleave unpredictably, causing incorrect final values.
Example: If both processes access count concurrently, the final value depends on instruction execution order rather than logical program flow.
Critical Sections
Solution approach: Model the problem using critical sections - code regions where processes access shared data. The system must ensure only one process can execute in its critical section at any time.
Structure: Processes use entry code (to coordinate access) and exit code (to signal completion) around their critical sections.
The lecture sets up the foundation for discussing synchronization mechanisms that solve these concurrency problems.
