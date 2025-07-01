# Lecture 27: Memory Management and Address Translation
## Operating Systems (CS330) - IIT Kanpur

This document covers key concepts in memory management, focusing on segmentation, paging, and demand paging mechanisms in operating systems.

## Table of Contents
- [Segmentation](#segmentation)
- [Linear to Physical Address Translation](#linear-to-physical-address-translation)
- [Demand Paging](#demand-paging)
- [Memory Hierarchy Extension](#memory-hierarchy-extension)
- [Optimization Techniques](#optimization-techniques)

## Segmentation

The Intel x86 architecture implements a segmentation system with two types of segment tables:

### Segment Tables
- **LDT (Local Descriptor Table)**: One per process
- **GDT (Global Descriptor Table)**: System-wide shared table

### Segment Descriptors
Each GDT or LDT entry contains:
- **32-bit starting linear address** for the segment
- **Segment size**
- **Privilege level** indicating processor modes where segment can be used
- **Access modes** (read, write, execute permissions)

The segment register value identifies both the descriptor table (GDT or LDT) and the specific descriptor within that table.

## Linear to Physical Address Translation

The system uses a **2-level paging scheme** for translating linear addresses to physical addresses.

### Address Structure (32-bit)
```
| 10 bits | 10 bits | 12 bits |
|---------|---------|---------|
|Page Dir |Page Tbl | Offset  |
|Index    |Index    |         |
```

- **Bits 31-22**: Index into page directory (first level)
- **Bits 21-12**: Index into second level page table
- **Bits 11-0**: Offset within the page

### Key Properties
- **Page size**: 4KB (2^12 bytes)
- **Two-level hierarchy** reduces memory overhead for page tables
- **Hardware-supported** translation process

## Demand Paging

Demand paging is a memory management technique that allows efficient use of physical memory.

### Core Concept
- Not all pages of a process's virtual address space need to be in physical memory simultaneously
- Pages can be **"paged out"** to a swap device (typically disk storage)
- Pages are loaded into memory **on-demand** when accessed

### Implementation Details
- **Valid bit** in page table entries indicates if page is in memory
- For paged-out pages:
  - Valid bit = 0
  - Page table entry stores disk address instead of physical frame number
- **Page fault exception** occurs when accessing paged-out pages

### Page Fault Handling Process
1. Process attempts to access paged-out page
2. Hardware generates page fault exception (valid bit = 0)
3. Exception handler:
   - Brings page from disk to memory
   - Updates page table entry
   - Restarts the instruction

## Memory Hierarchy Extension

Demand paging conceptually extends the traditional memory hierarchy:

```
L1 Cache → L2 Cache → Main Memory → Swap Device (Disk)
```

### Characteristics
- **Main memory** acts as a cache for the swap device
- **Software-implemented** level of memory hierarchy
- **Disk storage** is slower but has larger capacity
- Similar to cache management but at the OS level

## Optimization Techniques

### Dirty Bit Optimization
The system optimizes disk writes using dirty bits:

#### Hardware Support
- **Dirty bit** in page table entries tracks modifications
- Set by hardware when page is written to
- Cleared by OS when page is loaded from disk
- Page only written to disk if dirty (modified since last disk read)

#### Software Simulation
If hardware doesn't support dirty bits:
- OS can simulate using **protection bits**
- Initially deny write permission for writable pages
- On write attempt, hardware generates protection fault
- Fault handler:
  - Verifies write permission
  - Marks page as dirty
  - Enables write permission

### Benefits
- **Reduced disk I/O**: Only modified pages are written back
- **Improved performance**: Fewer expensive disk operations
- **Efficient memory utilization**: Better use of available physical memory

## Key Takeaways

1. **Segmentation** provides memory protection and organization
2. **Two-level paging** efficiently translates virtual to physical addresses
3. **Demand paging** allows programs larger than physical memory to run
4. **Memory hierarchy extension** treats main memory as a cache for disk storage
5. **Dirty bit optimization** minimizes unnecessary disk writes

---

*This document is based on Lecture 27 from CS330 Operating Systems course at IIT Kanpur.*
