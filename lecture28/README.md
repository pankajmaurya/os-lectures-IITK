# Operating Systems Lecture 28: Page Replacement Policies

## Overview
This lecture covers page replacement policies in operating systems, focusing on their implementation and performance characteristics when physical memory is insufficient to hold all required pages.

## Key Concepts

### Page Replacement Policy
A page replacement policy determines which page should be evicted from memory when no free pages are available. Unlike cache replacement policies implemented in hardware, page replacement policies are implemented by the operating system.

**Goals:**
- Minimize page fault rate
- Keep storage and computation overhead low

### Reference String
The sequence of virtual page numbers generated during program execution, used to evaluate policy performance by counting page faults for a given memory size.

## Page Replacement Algorithms

### 1. Optimal Policy (OPT)
- **Strategy**: Replace the page that will be used after the longest time in the future
- **Performance**: Lowest page fault rate theoretically possible
- **Implementation**: Cannot be implemented in practice (requires future knowledge)
- **Purpose**: Serves as a benchmark for comparing other policies

### 2. First-In-First-Out (FIFO)
- **Strategy**: Replace the oldest page in memory based on arrival time
- **Implementation**: Uses a pointer to track the last replaced frame
- **Advantages**: Simple to implement
- **Disadvantages**: 
  - Poor performance (may evict heavily used pages)
  - Suffers from Belady's Anomaly

#### Belady's Anomaly
A counterintuitive phenomenon where increasing the number of available frames can actually increase the number of page faults for the same reference string.

### 3. Least Recently Used (LRU)
- **Strategy**: Replace the page that hasn't been used for the longest time
- **Basis**: Locality of reference principle
- **Performance**: Generally good, approximates optimal behavior

## Locality of Reference

Programs exhibit two types of locality:
1. **Temporal Locality**: Recently accessed pages are likely to be accessed again soon
2. **Spatial Locality**: Pages near recently accessed pages are likely to be accessed

A locality is a set of pages actively used together, and programs move from one locality to another during execution.

## LRU Approximation Algorithms

Since exact LRU can be expensive to implement, several approximation methods exist:

### Reference Bit Approach
- **Hardware Support**: Each page table entry has a reference bit
- **Operation**: Hardware sets bit to 1 when page is referenced
- **Overhead**: Minimal space and time cost

### Additional Reference Bits Algorithm
- **Method**: Maintains history bits for each physical frame
- **Operation**: Periodically transfers reference bit to history bits using:
  ```
  history = (history >> 1) | R << (n-1)
  ```
- **Selection**: Frame with lowest history value is chosen as victim
- **Limitation**: High overhead from periodic updates limits practical use

## Implementation Considerations

- Page replacement policies require careful balance between accuracy and efficiency
- Hardware support (like reference bits) can significantly reduce software overhead
- More approximate but efficient algorithms are often preferred in practice
- Shared frames require special handling (logical OR of reference bits)

## Performance Evaluation

Page replacement policies are evaluated by:
- Running them on specific reference strings
- Counting page faults for given memory sizes
- Comparing results against the optimal policy benchmark

---

*Based on CS330 Operating Systems course material from IIT Kanpur*
