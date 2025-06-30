# CPU Scheduling

> **Course:** CS330 - Operating Systems  
> **Institution:** IIT Kanpur  
> **Lecture:** 22

## Overview

CPU scheduling is the foundation of multiprogramming systems. It determines which process runs on the CPU at any given time, with the primary objective of maximizing CPU utilization and system performance.

## Table of Contents

- [Core Concepts](#core-concepts)
- [Process Behavior](#process-behavior)
- [Scheduling Algorithms](#scheduling-algorithms)
  - [First Come First Serve (FCFS)](#first-come-first-serve-fcfs)
  - [Shortest Job First (SJF)](#shortest-job-first-sjf)
  - [Shortest Remaining Time First](#shortest-remaining-time-first)
  - [Priority-Based Scheduling](#priority-based-scheduling)
  - [Round-Robin Scheduling](#round-robin-scheduling)
  - [Multilevel Queue Scheduling](#multilevel-queue-scheduling)
- [Performance Metrics](#performance-metrics)
- [Trade-offs](#trade-offs)

## Core Concepts

### Multiprogramming Objective
- **Goal:** Keep some process running at all times to maximize CPU utilization
- **Challenge:** On uni-processor systems, only one process can run at a time
- **Solution:** When a process waits (for I/O, locks, etc.), switch to another ready process

### Ready Queue
The operating system maintains a **ready queue** containing processes that are ready to execute. The scheduler selects processes from this queue when the CPU becomes available.

### When CPU Scheduling Occurs
- Process switches from running to waiting state
- Process switches from running to ready state (preemption)
- Process switches from waiting to ready state
- Process terminates

## Process Behavior

### CPU and I/O Bursts
- Processes alternate between **CPU bursts** (computation) and **I/O bursts** (waiting)
- Process lifecycle: CPU burst → I/O burst → CPU burst → ... → final CPU burst → terminate

### Burst Characteristics
- **Interactive programs:** Short CPU bursts
- **Compute-intensive programs:** Long CPU bursts
- **Distribution:** Most CPU bursts are exponentially distributed and very small

## Scheduling Algorithms

### First Come First Serve (FCFS)

**Characteristics:**
- Non-preemptive FIFO queue
- Simple implementation
- No starvation

**Problems:**
- **Convoy Effect:** Short jobs wait for long jobs, leading to poor CPU and device utilization
- High waiting times for short processes
- Poor response time for interactive jobs

```
Example: If a CPU-bound job runs first, I/O devices become idle while other 
processes wait, then CPU becomes idle when all processes start I/O together.
```

### Shortest Job First (SJF)

**Characteristics:**
- Priority queue based on next CPU burst length
- **Optimal:** Provably minimum average waiting time among non-preemptive algorithms
- Non-preemptive

**Challenge:** Predicting CPU burst lengths

**Prediction Formula:**
```
τₙ₊₁ = α × tₙ + (1 - α) × τₙ
```
Where:
- `τᵢ` = estimated length of ith burst
- `tᵢ` = actual length of ith burst  
- `α` = constant between 0 and 1

**Expanded Form:**
```
τₙ₊₁ = α×tₙ + (1-α)×α×tₙ₋₁ + (1-α)²×α×tₙ₋₂ + ... + (1-α)ⁿ⁺¹×α×t₀
```

### Shortest Remaining Time First

**Characteristics:**
- Preemptive version of SJF
- Can interrupt running process for shorter new arrival
- **Optimal:** Minimum average waiting time among ALL scheduling algorithms

### Priority-Based Scheduling

**Characteristics:**
- Assigns priorities to processes
- Scheduler always chooses highest priority runnable process
- Can be preemptive or non-preemptive
- SJF is a special case (priority = burst length)

**Problems:**
- **Starvation:** High-priority processes may prevent low-priority ones from running
- **Priority Assignment:** How to fairly assign priorities?

### Round-Robin Scheduling

**Characteristics:**
- FIFO queue with **time quantum** (typically 100-200ms)
- Process runs for at most one quantum, then moves to end of queue
- Preemptive

**Advantages:**
- Bounded waiting and response times
- Fair sharing of CPU time

**Time Quantum Selection:**
- **Too large:** Degenerates to FCFS
- **Too small:** High context switch overhead, reduced throughput
- **Optimal:** Most CPU bursts should be smaller than quantum

### Multilevel Queue Scheduling

**Structure:**
- Processes categorized into distinct classes:
  - System processes
  - Interactive processes  
  - Batch processes
- Each class has different priority
- Higher priority classes have absolute precedence

**Scheduling Within Classes:**
- Different algorithms for different classes
- Example: Round-robin for interactive, FCFS for batch

**Starvation Prevention:**
- Allocate fixed CPU time proportions to classes
- Example: Background class gets 20% of CPU time

## Performance Metrics

### Key Metrics
- **CPU Utilization:** Percentage of time CPU is busy
- **Throughput:** Number of processes completed per time unit
- **Turnaround Time:** Time from submission to completion
- **Waiting Time:** Time spent in ready queue
- **Response Time:** Time from submission to first response

### Ideal Scheduling Algorithm
Would maximize CPU utilization and throughput while minimizing turnaround time, waiting time, and response time.

## Trade-offs

### Conflicting Objectives
- **Response Time vs. Throughput:** Frequent context switches improve response time but reduce throughput due to overhead
- **Fairness vs. Performance:** Fair algorithms may not be optimal for performance
- **Predictability vs. Adaptability:** Simple algorithms are predictable but may not adapt to changing workloads

### System Considerations
- **Job Mix:** Different algorithms suit different workload types
- **General Purpose Systems:** Assume mix of interactive and compute-intensive jobs
- **Burst Prediction Accuracy:** SJF performance depends heavily on accurate predictions

## Conclusion

CPU scheduling algorithm choice depends on:
- Expected job mix and characteristics
- System requirements and priorities  
- Balance between competing performance metrics

Most modern operating systems use sophisticated combinations of these basic algorithms to handle diverse workloads effectively.

---

*This document summarizes CPU scheduling concepts from CS330 Operating Systems course at IIT Kanpur.*
