# Operating Systems (CS330) - Lecture 25: Memory Management

## Overview
This lecture covers memory management techniques in operating systems, specifically focusing on virtual memory implementation and segmentation. The content explores various approaches to address translation and their associated challenges and benefits.

## Table of Contents
- [Simple Translation Schemes](#simple-translation-schemes)
- [Contiguous Memory Allocation](#contiguous-memory-allocation)
- [Segmentation](#segmentation)
- [Advantages of Segmentation](#advantages-of-segmentation)
- [Limitations](#limitations)

## Simple Translation Schemes

### Basic Address Translation
- **Mechanism**: Uses base and limit registers for each process
- **Process**: 
  1. OS maintains base (S) and limit (L) values for each process
  2. Hardware registers store current process values
  3. For virtual address `v`: check if `v < limit`, then calculate physical address as `v + base`
- **Exception Handling**: Illegal addresses (v ≥ limit) raise exceptions

## Contiguous Memory Allocation

### Major Problems

#### External Fragmentation
- **Cause**: Dynamic process creation/termination creates scattered free memory chunks
- **Impact**: Small fragments become too small for any process
- **Overhead**: Tracking tiny fragments may require more memory than the fragment size

#### Internal Fragmentation
- **Cause**: Allocating slightly more memory than needed to avoid tiny fragments
- **Impact**: Memory waste within allocated blocks

### Solutions and Limitations

#### Compaction
- **Goal**: Shuffle allocated chunks to create single large free block
- **Drawback**: High overhead due to extensive data movement

#### Runtime Memory Requests
- **Problem**: Difficult to accommodate growth requests
- **Solution**: Copy entire process to larger chunk (expensive operation)

## Segmentation

### Structure
- **Virtual Address Components**:
  - Segment number (k most significant bits)
  - Offset within segment (remaining n-k bits)
- **Limits**: 
  - Maximum segments: 2^k
  - Maximum segment size: 2^(n-k) bytes

### Implementation
- **Physical Layout**: Segments occupy contiguous physical memory portions
- **Flexibility**: Segments need not be physically contiguous to each other
- **Segment Table**: Stores base and limit values for each segment
  - Indexed by segment number
  - Can be stored in memory or dedicated fast memory

### Translation Process
1. Extract segment number and offset from virtual address
2. Use segment number to index segment table
3. Retrieve base and limit values
4. Compare offset with limit (raise exception if offset ≥ limit)
5. Calculate physical address: base + offset

### Additional Features
- **Valid Bits**: Indicate whether segments are defined/valid
- **Protection Bits**: Support different access levels (read, write, execute)

## Advantages of Segmentation

### 1. Enhanced Protection
- **Access Control**: Different segments can have different access rights
- **Implementation**: Protection bits in segment table entries
- **Runtime Checking**: Access permissions verified during translation

### 2. Memory Sharing
- **Use Case**: Multiple processes executing the same program
- **Implementation**: 
  - Code segments marked read-only
  - Same segment table entries across processes
  - Single copy in physical memory
- **Benefits**: Significant memory savings
- **Applications**: Shared memory IPC implementation

### 3. Flexibility
- **Variable Sizing**: Segments can be different sizes
- **Non-contiguous Placement**: Segments can be placed anywhere in physical memory

## Limitations

### Persistent External Fragmentation
- **Issue**: Variable-sized segments still require contiguous physical memory chunks
- **Impact**: External fragmentation problem remains unsolved
- **Solution Preview**: Paging technique (covered in next lecture) addresses this limitation

## Key Takeaways

1. **Evolution**: Segmentation improves upon simple contiguous allocation
2. **Trade-offs**: Gains flexibility and protection but retains fragmentation issues
3. **Foundation**: Sets groundwork for more advanced techniques like paging
4. **Practical Applications**: Enables memory sharing and protection mechanisms essential for modern operating systems

## Course Information
- **Course**: CS330 - Operating Systems
- **Institution**: IIT Kanpur
- **Lecture**: 25 (Memory Management Series)

---

*Note: This lecture is part of a series on virtual memory implementation. The next lecture will cover paging as a solution to external fragmentation.*
