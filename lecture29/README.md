# Operating Systems Lecture 29: Page Replacement Algorithms and Memory Management

**Course:** CS330 - Operating Systems  
**Lecturer:** Deepak Gupta  
**Notes by:** Anoop Kumar  
**Date:** October 11, 2004  

## Overview

This lecture covers advanced page replacement algorithms, thrashing, swapping, and other memory management techniques used in operating systems.

## Topics Covered

### 1. Clock Algorithm (Second Chance Algorithm)

The clock algorithm improves upon FIFO by giving recently used pages a "second chance" before eviction.

**Key Features:**
- Physical memory frames arranged in a circular array
- Clock hand points to frame following last replaced frame
- Reference bit used to track page usage
- Pages with reference bit = 1 get another chance before eviction

**Implementation in 4.2BSD:**
- Uses `pagedaemon` process to maintain free memory
- Three key parameters:
  - `minfree`: minimum tolerable free memory (1/16 of total memory)
  - `desfree`: desirable free memory (1/8 of total memory)  
  - `lotsfree`: threshold to stop page reclamation (1/4 of total memory)
- Pagedaemon runs 4 times per second or on page faults
- `scanrate` determines reclamation speed based on free memory

### 2. Two Hand Clock Algorithm (4.3BSD)

Enhanced version that addresses the clock algorithm's dependency on memory size.

**Improvements:**
- Two clock hands maintain fixed distance apart
- Front hand clears reference bits
- Back hand reclaims pages with unset reference bits
- Fixed separation ensures consistent timing regardless of memory size

### 3. Working Set and Thrashing

**Working Set:** Set of pages actively used by a process at any given time (current locality).

**Thrashing:** Occurs when a process cannot keep its working set in memory, leading to:
- Excessive page faults
- More time spent on page fault handling than computation
- Drastically reduced CPU utilization and system throughput

**System Behavior:**
- Low multiprogramming: High CPU utilization (working sets fit in memory)
- High multiprogramming: Thrashing occurs, CPU utilization drops sharply

### 4. Swapping

**Purpose:** Reduce multiprogramming degree to avoid/recover from thrashing.

**Process:**
- Swap out entire processes (page tables + memory-resident pages) to swap device
- Swapped processes cannot run, reducing memory competition
- Form of "long-term scheduling" vs "short-term scheduling" (CPU scheduling)

**Swapping in BSD:**

#### Swapping In
**Priority factors for swap-in decisions:**
- Time swapped out (longer = higher priority)
- Resident set size when swapped out (smaller = higher priority)
- Process nice value (lower = higher priority)
- Sleep duration (longer = higher priority)

**Conditions:**
- Process swapped in with half memory if swapped out >10 seconds
- Force swap-out of sleeping process (>20 seconds) if needed
- Prevents processes from remaining swapped out too long

#### Swapping Out
**Triggers:**
- Long-term free memory average < `desfree`
- Short-term free memory average < `minfree` 
- Need memory for swap-in operation

**Selection criteria:**
- Sleeping processes (>20 seconds): Longest sleeper chosen
- Active processes: Select from 4 largest, choose longest in memory

### 5. Additional Memory Management Techniques

#### Prepaging
- Bring pages to memory before program execution
- Examples: Entry point code page, initial stack page
- Useful during process swap-in (restore previous resident set)
- Reduces page faults by anticipating memory needs

#### Copy on Write (COW)
**Mechanism:** Efficiently share pages between processes until modification occurs.

**Implementation:**
- Processes share same physical frame initially
- Write permissions removed for both processes
- Frame marked as copy-on-write
- Protection fault triggers actual copying when write attempted
- Write permission restored when only one process remains

**Benefits:**
- Efficient `fork()` implementation
- Reduces memory usage for shared, unmodified data
- Defers costly copying until actually needed

## Key Takeaways

1. **Algorithm Evolution:** From simple FIFO to sophisticated clock algorithms addressing real-world performance issues

2. **Thrashing Management:** Critical to maintain balance between multiprogramming degree and memory availability

3. **Swapping Strategy:** Long-term scheduling mechanism essential for system stability under memory pressure

4. **Optimization Techniques:** Prepaging and copy-on-write provide significant performance improvements through intelligent memory management

5. **System Parameters:** Careful tuning of thresholds (`minfree`, `desfree`, `lotsfree`) crucial for optimal performance

This lecture demonstrates how operating systems evolved sophisticated memory management strategies to handle the fundamental challenge of limited physical memory in multiprogrammed environments.
