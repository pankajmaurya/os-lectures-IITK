# Paging in Operating Systems

## Overview

This document summarizes key concepts from Lecture 26 of Operating Systems (CS330) covering **Paging** as a memory management technique.

## Table of Contents

- [Introduction](#introduction)
- [How Paging Works](#how-paging-works)
- [Address Translation](#address-translation)
- [Advantages](#advantages)
- [Disadvantages](#disadvantages)
- [Two-Level Paging](#two-level-paging)
- [Key Takeaways](#key-takeaways)

## Introduction

Paging is a memory management scheme designed to solve the **external fragmentation** problem that affects both Contiguous Memory Allocation and Segmentation techniques. External fragmentation occurs when physical memory is allocated in variable-sized contiguous chunks, leading to unusable memory gaps.

## How Paging Works

Paging eliminates external fragmentation by ensuring that all requests for contiguous chunks of physical memory are always the same size:

- **Virtual address space** is divided into equal-sized **pages**
- Each accessible page maps to an equal-sized **physical memory frame**
- Contiguous pages in virtual memory **do not** need to map to adjacent frames in physical memory
- A **page table** maintains the mapping from virtual pages to physical frames

## Address Translation

The address translation process in paging works as follows:

1. A virtual address is divided into two components:
   - **Page number (p)** - used as an index into the page table
   - **Page offset (d)** - offset within the page

2. The page table entry contains the **frame number** of the corresponding physical frame

3. The frame number is combined with the page offset to obtain the final physical memory address

### Page Table Entries

Each page table entry typically contains:
- Physical frame number
- Valid bit
- Protection bits
- Additional bits for demand paging support

## Advantages

✅ **Eliminates External Fragmentation**: All memory requests are uniform in size (page/frame size)

✅ **Flexible Memory Allocation**: Virtual pages don't need to map to contiguous physical frames

✅ **Better Memory Utilization**: More efficient use of available physical memory

## Disadvantages

❌ **Internal Fragmentation**: Memory allocated in page units may exceed actual requirements
- Example: 1KB frame size, 8604 bytes needed → 9 pages allocated (9216 bytes) → 612 bytes wasted
- On average, half a page is wasted per process

❌ **Large Page Table Overhead**: 
- 32-bit system with 4KB pages and 4-byte entries = 4MB page table per process
- Page table size often exceeds actual process memory requirements

## Two-Level Paging

To address the page table size problem, **two-level paging** was introduced:

### How It Works
- Similar to segmentation but with paged segments
- First-level page table points to second-level page tables
- Second-level page tables contain actual frame mappings

### Benefits
- **Reduced Memory Overhead**: Second-level page tables only exist when needed
- **Efficient Invalid Region Handling**: Large invalid virtual address regions marked with minimal overhead
- **Shared Memory Support**: Processes can share page tables for shared segments

### Memory Savings
Particularly effective for small processes with sparse memory usage patterns, significantly reducing overall page table memory requirements.

## Key Takeaways

1. **Paging trades external fragmentation for internal fragmentation**
2. **Page size selection is crucial** - larger pages reduce page table overhead but increase internal fragmentation
3. **Two-level paging effectively addresses page table size issues** for most practical applications
4. **Memory sharing becomes more efficient** with hierarchical page table structures

---

*Based on CS330 Operating Systems Lecture 26 - Paging*
