# Process Management - Operating Systems Lecture 6

**Course**: Operating Systems (CS330)  
**Institution**: IIT Kanpur  
**Lecturer**: Deepak Gupta  
**Notes by**: Ankit Soni  
**Date**: August 7, 2004

## Overview

This lecture introduces the fundamental concepts of process management in operating systems, covering the transition from single-program execution to multi-programmed environments and the abstractions needed to manage concurrent program execution.

## Table of Contents

- [Process Fundamentals](#process-fundamentals)
- [Process Components](#process-components)
- [Process States](#process-states)
- [State Transitions](#state-transitions)
- [Scheduling](#scheduling)

## Process Fundamentals

### Need for Processes

Early computer systems were limited to executing only one program at a time, with that program having complete control over system resources. Modern computing environments require:

- **Concurrent execution** of multiple programs
- **Multiple instances** of the same program running simultaneously
- **Better control and compartmentalization** of program execution

This evolution led to the development of the **process concept**.

### Process vs Program

| Aspect | Program | Process |
|--------|---------|---------|
| **Nature** | Passive entity | Active entity |
| **Definition** | Code stored in files or written form | "Program in execution" |
| **Abstraction** | Static code | Virtual computer |
| **Instances** | Single code base | Multiple execution sequences possible |

**Key Insight**: Multiple processes can execute the same program code but maintain separate execution contexts and data.

## Process Components

### What Makes Up a Process

A process consists of three main components:

1. **Virtual Address Space** - Memory layout for the process
2. **CPU Register Values** - Current execution state
3. **OS State Information** - Metadata maintained by the kernel

### Process Control Block (PCB)

The PCB is the primary data structure used by the operating system to manage processes. It contains:

- **Process Identification**
  - Process ID (PID)
  - User ID of owner

- **Memory Management**
  - Address translation tables

- **Process State**
  - Current state (new, ready, running, waiting, terminated)

- **CPU Context**
  - Saved CPU register values
  - CPU scheduling information
  - Priority and resource usage data

- **I/O Management**
  - List of open files
  - I/O status information

## Process States

Every process exists in exactly **one** of the following states at any given time:

### State Definitions

| State | Description | Characteristics |
|-------|-------------|-----------------|
| **New** | Process being created | PCB not fully initialized |
| **Running** | Currently executing | Only one process in uniprocessor systems |
| **Ready** | Ready to run, waiting for CPU | Multiple processes possible, stored in Ready Queue |
| **Blocked/Waiting** | Waiting for event completion | I/O operations, resource availability |
| **Terminated** | Process finished execution | Zombie state in UNIX, minimal info retained |

### Important Notes

- Only **one process** can be in the Running state on a uniprocessor system
- The kernel maintains a global variable (`current` in Linux) pointing to the running process
- **Ready Queue** contains all processes eligible for CPU scheduling
- Terminated processes retain minimal information until collected by other processes

## State Transitions

```
New → Ready → Running → Terminated
        ↕         ↓
      Ready ← Blocked/Waiting
```

### Transition Details

| Transition | Trigger | Description |
|------------|---------|-------------|
| **new → ready** | Process admitted | Initialization complete, ready for scheduling |
| **ready → running** | Scheduler selection | CPU scheduler chooses process based on policy |
| **running → ready** | Preemption | Time slice expired, forced CPU relinquishment |
| **running → blocked** | Event wait | Process waits for I/O or resource |
| **blocked → ready** | Event completion | Awaited event occurs, process becomes schedulable |

### Critical Rules

- **No direct blocked → running transition** - Processes must go through ready state
- **No direct blocked → terminated transition** - Generally not allowed

## Scheduling

### Definition

**Scheduling** is the process of:
1. Deciding which ready process should run next on the CPU
2. Performing a **context switch** to transfer control

### When Scheduling Occurs

| Scenario | Necessity | Type |
|----------|-----------|------|
| **Process Termination** | Must schedule | Mandatory |
| **Process Blocking** | Must schedule | Mandatory |
| **Timer Interrupt** | May schedule | Optional (Policy-dependent) |

### Scheduling Types

- **Preemptive Scheduling**: OS can forcibly remove processes from CPU
- **Non-preemptive Scheduling**: Processes voluntarily relinquish CPU control

### Key Concepts

- **Context Switch**: The mechanism of saving current process state and loading new process state
- **Time Sharing**: CPU time is divided among multiple processes
- **Preemption**: Forced removal of a process from CPU execution

## Summary

This lecture establishes the foundational concepts of process management:

- **Processes** are active abstractions of program execution
- **PCB** serves as the central data structure for process management
- **Process states** provide a framework for understanding execution flow
- **Scheduling** enables efficient CPU utilization through time sharing

These concepts form the basis for understanding advanced topics in operating systems, including process synchronization, memory management, and system performance optimization.

---

*This README summarizes the key concepts from Lecture 6 of the Operating Systems course at IIT Kanpur. For complete details, refer to the original lecture notes.*
