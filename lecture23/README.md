# CPU Scheduling (Advanced Algorithms)

> **Course**: Operating Systems (CS330)  
> **Lecturer**: Deepak Gupta  
> **Lecture**: 23  
> **Date**: Aug 21, 2004  

## Overview

This document covers advanced CPU scheduling algorithms used in real-world operating systems, focusing on multilevel feedback queue scheduling and its implementations in BSD, Linux, and Solaris.

## Table of Contents

- [Multilevel Feedback Queue Scheduling](#multilevel-feedback-queue-scheduling)
- [BSD Unix Scheduling](#bsd-unix-scheduling)
- [Linux Scheduling](#linux-scheduling)
- [Solaris Scheduling](#solaris-scheduling)

## Multilevel Feedback Queue Scheduling

### Core Concept

The foundation of modern OS scheduling algorithms that allows processes to move between different priority queues based on their runtime behavior.

### Key Principles

- **Interactive Jobs**: Higher priority (require quick response times)
- **Compute-Intensive Jobs**: Lower priority (longer CPU bursts)
- **Feedback Mechanism**: Priorities adjust based on past performance
- **Anti-Starvation**: Prevents low-priority processes from being indefinitely delayed

### Process Classification

| Process Type | CPU Burst | I/O Burst | Priority |
|--------------|-----------|-----------|----------|
| Interactive | Short | Long | High |
| Compute-Intensive | Long | Short | Low |

### Configuration Parameters

1. **Number of queues**
2. **Scheduling discipline within each queue**
3. **Promotion/demotion rules**
4. **Default queue assignment**

## BSD Unix Scheduling

### System Characteristics

- **Priority Levels**: 128 (0-127, higher number = lower priority)
- **Scheduling Algorithm**: Round-robin within each level
- **Time Quantum**: 100ms
- **Preemption**: Only when quantum expires (non-preemptive kernel)
- **Selection**: Always picks first process in highest priority non-empty queue

### Priority Computation

```
priority = PUSER + ⌈p_cpu/4⌉ + p_nice
```

#### Components

| Component | Description | Range/Value |
|-----------|-------------|-------------|
| `PUSER` | Constant for user processes (system processes use `PSYS`) | Constant |
| `p_cpu` | Accumulated CPU time in clock ticks | 0+ |
| `p_nice` | User-controllable priority influence | -32 to 32 (default: 0) |

### Digital Decay Filter

Applied every second to prevent starvation:

```
p_cpu = p_cpu(2.load)/(2.load + 1) + p_nice
```

Where `load` is the average run queue length over the last minute.

#### For Sleeping Processes

```
p_cpu = p_cpu[(2.load)/(2.load + 1)]^sleeptime
```

**Benefits**:
- Exponential decay prevents indefinite penalization
- Load-aware adjustment
- Sleeping processes get slight advantage

## Linux Scheduling

### Core Features

- **Base Algorithm**: Round-robin variation
- **Quantum Assignment**: Depends on nice value
- **Key Innovation**: Unused quantum portions are preserved
- **Preemption**: Only on quantum completion

### Process Fields

| Field | Description |
|-------|-------------|
| `priority` | Full time quantum amount for the process |
| `counter` | Remaining time in current quantum |

### Scheduling Logic

1. **Process Selection**: Highest `counter` value runs next
2. **Quantum Refresh**: When all counters reach 0:
   ```
   counter = (counter/2) + priority
   ```
3. **Sleeping Process Advantage**: Retain half of unused quantum

### Advantages

- Rewards processes that yield CPU voluntarily
- Balances interactive responsiveness with fairness
- Simple implementation with effective results

## Solaris Scheduling

### System Architecture

- **Priority Levels**: 170 (higher number = higher actual priority)
- **Preemption**: Can occur when higher-priority process wakes up
- **Design**: Table-driven scheduler
- **Process Classes**: System, real-time, interactive, timesharing, etc.

### Timesharing Class (Priority 0-59)

Uses preemptive scheduling with round-robin within each priority level.

### Dispatch Table Parameters

| Parameter | Description | Typical Values |
|-----------|-------------|----------------|
| `quantum` | Time slice for priority level | Higher at lower priorities |
| `tqexp` | Priority after quantum expires | ~10 levels below current |
| `slpret` | Priority when process wakes up | 50-59 range |
| `maxwait` | Max wait time before promotion | Default: 0 seconds |
| `lwait` | Priority after maxwait exceeded | 50-59 range |

### Anti-Starvation Mechanism

- Processes waiting > `maxwait` seconds get promoted to `lwait` priority
- Default promotes waiting processes to high priority (50-59) after 1 second
- Ensures compute-intensive processes don't starve

## Key Takeaways

### Design Trade-offs

1. **Responsiveness vs. Fairness**: Interactive processes get priority without completely starving compute-intensive ones
2. **Complexity vs. Performance**: More sophisticated algorithms provide better user experience
3. **Overhead vs. Precision**: Frequent priority recalculation improves scheduling but increases system overhead

### Common Patterns

- **Priority Decay**: All systems use some form of priority reduction over time
- **Sleep Rewards**: Processes that yield CPU get scheduling advantages
- **Load Awareness**: System load influences scheduling decisions
- **Anti-Starvation**: Mechanisms prevent indefinite waiting

### Evolution

These algorithms represent the evolution from simple round-robin to sophisticated multilevel feedback systems that adapt to process behavior and system conditions.

---

*Notes prepared by: Rachna Agarwal*  
*Source: [Original Lecture](https://pankajmaurya.github.io/os-lectures-IITK/lecture23/default.html)*
