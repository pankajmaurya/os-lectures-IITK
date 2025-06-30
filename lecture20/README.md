# Deadlocks in Operating Systems

## Overview

This document covers the fundamental concepts of deadlocks in operating systems, based on Lecture 20 from CS330 at IIT Kanpur. A **deadlock** occurs when a set of processes are all waiting for events that can only be caused by other processes in the same set, creating a situation where all processes wait indefinitely.

## Table of Contents

- [System Model](#system-model)
- [Necessary Conditions for Deadlock](#necessary-conditions-for-deadlock)
- [Resource Allocation Graph](#resource-allocation-graph)
- [Approaches for Handling Deadlocks](#approaches-for-handling-deadlocks)
- [Deadlock Prevention](#deadlock-prevention)
- [The Dining Philosophers Problem](#the-dining-philosophers-problem)
- [Solutions to Dining Philosophers](#solutions-to-dining-philosophers)

## System Model

Deadlocks in this context are caused by shared resources, which can be:
- **Physical resources**: Printers, scanners, disk drives
- **Logical resources**: Locks, mutexes, semaphores, file handles

### Resource Organization
- Resources are divided into **resource types**
- Each resource type has a fixed number of **identical instances**
- A process can request any instance of a resource type
- Processes must **request** resources before using them
- If resources aren't available immediately, the process **waits**

## Necessary Conditions for Deadlock

All four conditions must be present simultaneously for a deadlock to occur:

### 1. Mutual Exclusion
- At least one resource can only be used by one process at a time
- Cannot be shared simultaneously among multiple processes

### 2. No Preemption
- A process cannot be forced to give up resources it's currently holding
- Resources are released only voluntarily by the holding process

### 3. Hold and Wait
- At least one process holds some resources while waiting for additional resources
- Process doesn't release currently held resources while waiting

### 4. Circular Wait
- A circular chain of processes exists where each process waits for resources held by the next process in the chain
- P₁ → P₂ → P₃ → ... → Pₙ → P₁

> **Note**: These conditions are **necessary** but not **sufficient** for deadlock occurrence.

## Resource Allocation Graph (RAG)

A Resource Allocation Graph is a visual representation of the current system state regarding resource allocation and requests.

### Components
- **Circles**: Represent processes
- **Rectangles**: Represent resource types
- **Dots inside rectangles**: Represent individual resource instances
- **Directed edges**:
  - **Request edge**: Process → Resource (process waiting for resource)
  - **Assignment edge**: Resource → Process (resource allocated to process)

### Deadlock Detection in RAG
- **Cycle presence**: If a cycle exists in the RAG, deadlock is possible
- **Cycle absence**: No deadlock can exist
- **Important**: Cycles are necessary but not sufficient for deadlock

## Approaches for Handling Deadlocks

### 1. Deadlock Prevention
- Design programs to ensure at least one necessary condition never holds
- **Advantage**: Guarantees no deadlocks
- **Disadvantage**: May reduce system efficiency

### 2. Deadlock Avoidance
- Runtime system monitors resource allocation
- Prevents system from entering deadlock states
- Uses algorithms like Banker's Algorithm

### 3. Deadlock Detection
- Allows deadlocks to occur
- Periodically checks for deadlocks
- Implements recovery mechanisms when deadlocks are detected

## Deadlock Prevention

Strategies to prevent each necessary condition:

### Preventing Mutual Exclusion
- **Approach**: Make all resources shareable
- **Problem**: Many resources are inherently non-shareable (locks, printers)
- **Feasibility**: Generally not practical

### Preventing No Preemption
- **Approach**: Force processes to release held resources
- **Application**: Works for some resources (CPU, memory)
- **Problem**: Not applicable to all resource types (what if we preempt a lock?)

### Preventing Hold and Wait
Two strategies:
1. **All-or-nothing allocation**: Process requests all needed resources at once
2. **Release-and-request**: Process releases all held resources before requesting new ones

**Drawbacks**: Poor resource utilization, potential starvation

### Preventing Circular Wait
- **Resource ordering**: Assign unique numbers to resource types
- **Protocol**: Process holding resource type `i` can only request resource type `j` where `j > i`
- **Result**: Creates a partial ordering that prevents cycles

## The Dining Philosophers Problem

The Dining Philosophers Problem is a classic synchronization problem that illustrates deadlock concepts.

### Problem Setup

```
        🍽️ P₀ 🍴
    🍴         🍴
 P₄ 🍽️         🍽️ P₁
    🍴         🍴
    P₃ 🍽️ 🍴 🍽️ P₂
```

- **n philosophers** sit around a circular table
- **n forks** placed between adjacent philosophers
- Each philosopher alternates between **thinking** and **eating**
- To eat, a philosopher needs **both adjacent forks**
- A fork can only be used by **one philosopher at a time**

### The Deadlock Scenario

#### Naive Solution (Deadlock-Prone)
```c
// Philosopher i's code
lock(fork[i]);           // Pick up left fork
lock(fork[(i+1) % n]);   // Pick up right fork
eat();                   // Eat spaghetti
unlock(fork[i]);         // Put down left fork
unlock(fork[(i+1) % n]); // Put down right fork
think();                 // Think
```

#### Deadlock Scenario Visualization

**Step 1**: All philosophers pick up their left fork simultaneously
```
        🍽️ P₀ 🔒
    ❌         🍴
 P₄ 🍽️         🍽️ P₁
    🔒         🔒
    P₃ 🍽️ 🔒 🍽️ P₂
```

**Step 2**: All philosophers wait for their right fork (DEADLOCK!)
```
        🍽️ P₀ 🔒 (waiting for fork)
    ❌                    ❌
 P₄ 🍽️ (waiting)    (waiting) 🍽️ P₁
    🔒                    🔒
    P₃ 🍽️ 🔒 🍽️ P₂
         (waiting for fork)
```

Each philosopher holds one fork and waits for another, creating a circular wait condition.

## Solutions to Dining Philosophers

### Solution 1: Limit Table Occupancy
**Strategy**: Allow at most (n-1) philosophers at the table

```
        🍽️ P₀ 🍴
    🍴         🍴
 -- 🚫         🍽️ P₁
    🍴         🍴
    P₃ 🍽️ 🍴 🍽️ P₂
```

**Why it works**: With n-1 philosophers and n forks, at least one philosopher can always eat
**Prevents**: Circular wait condition

### Solution 2: Atomic Fork Acquisition
**Strategy**: Pick up both forks simultaneously or none at all

```c
// Pseudo-code
if (both_forks_available(i, (i+1)%n)) {
    lock(fork[i]);
    lock(fork[(i+1) % n]);
    eat();
    unlock(fork[i]);
    unlock(fork[(i+1) % n]);
}
```

**Prevents**: Hold and wait condition

### Solution 3: Break Symmetry
**Strategy**: Even-numbered philosophers pick left fork first, odd-numbered pick right fork first

```
Philosopher 0, 2, 4: Left → Right
Philosopher 1, 3:    Right → Left
```

**Visualization**:
```
        🍽️ P₀ (L→R)
    🍴         🍴
 P₄(L→R)      P₁(R→L) 🍽️
    🍴         🍴
    P₃(R→L) 🍽️ 🍴 🍽️ P₂(L→R)
```

**Why it works**: Breaks the symmetry that causes all philosophers to perform the same action simultaneously
**Prevents**: Circular wait condition

### Solution 4: Resource Ordering
**Strategy**: Number the forks and always pick up the lower-numbered fork first

```
Fork numbers: 0, 1, 2, 3, 4 (for 5 philosophers)

Philosopher 0: fork 0, then fork 4  → pick fork 0 first
Philosopher 1: fork 1, then fork 0  → pick fork 0 first  
Philosopher 2: fork 2, then fork 1  → pick fork 1 first
Philosopher 3: fork 3, then fork 2  → pick fork 2 first
Philosopher 4: fork 4, then fork 3  → pick fork 3 first
```

**Implementation**:
```c
int left = i;
int right = (i + 1) % n;
int first = min(left, right);
int second = max(left, right);

lock(fork[first]);
lock(fork[second]);
eat();
unlock(fork[second]);
unlock(fork[first]);
```

**Why it works**: Creates a global ordering of resources that prevents circular dependencies
**Prevents**: Circular wait condition

## Key Takeaways

1. **Deadlock Prevention** is proactive but may reduce system efficiency
2. **Resource Allocation Graphs** help visualize and detect potential deadlocks
3. **All four conditions** must be present for deadlock to occur
4. **Breaking any one condition** prevents deadlock
5. **The Dining Philosophers Problem** provides an excellent model for understanding synchronization and deadlock issues

## Further Reading

- Deadlock Avoidance (Banker's Algorithm)
- Deadlock Detection Algorithms
- Recovery from Deadlock
- Advanced Synchronization Primitives

---

*Based on Lecture 20, Operating Systems (CS330), IIT Kanpur*  
*Lecturer: Deepak Gupta*  
*Original Notes: Abhimanyu Singh Sehkhawat*
