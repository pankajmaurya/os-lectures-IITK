# Operating Systems (CS330) - Lecture 21
## Safe, Unsafe and Deadlocked States

### Overview
This lecture covers deadlock handling mechanisms in operating systems, focusing on safe/unsafe states, deadlock avoidance algorithms, detection methods, and recovery strategies.

## Key Concepts

### Safe, Unsafe, and Deadlocked States

#### Safe States
A state is **safe** if the system can allocate the maximum required resources to all processes in some order, thus avoiding deadlock. This is determined by finding a "safe sequence."

#### Safe Sequences
A sequence of processes where each process can obtain its maximum resource needs using:
- Currently available resources
- Resources that will be released by previously completed processes in the sequence

#### Example
Consider a system with 12 instances of a single resource:

| Process | Max Requirement | Current Allocation |
|---------|-----------------|-------------------|
| P0      | 10              | 5                 |
| P1      | 4               | 2                 |
| P2      | 9               | 2                 |

**Available resources**: 3 instances

**Safe sequence**: P1 → P0 → P2
1. P1 gets 2 more instances (completes, releases 4)
2. P0 gets 5 more instances (completes, releases 10)  
3. P2 gets 7 more instances (completes)

#### Unsafe State Example
If P2 is granted one more resource:

| Process | Max Requirement | Current Allocation |
|---------|-----------------|-------------------|
| P0      | 10              | 5                 |
| P1      | 4               | 2                 |
| P2      | 9               | 3                 |

**Available resources**: 2 instances
- No safe sequence exists → **Unsafe state**

## Algorithms

### Banker's Algorithm

**Purpose**: Deadlock avoidance for multiple resource instances

**Complexity**: O(mn²) where:
- m = number of resource types
- n = number of processes

#### Data Structures
- **Available[m]**: Available instances of each resource type
- **Max[n][m]**: Maximum demand of each process
- **Allocation[n][m]**: Currently allocated resources
- **Need[n][m]**: Remaining resource need (Max - Allocation)

#### Algorithm Steps
1. When process Pi makes request Ri:
   - Check if Ri ≤ Need[i] and Ri ≤ Available
   - Simulate resource allocation
   - Run safety algorithm on resulting state
   - Grant request only if resulting state is safe

#### Safety Algorithm
```
Work = Available
Finish[i] = false for all i

While there exists i such that:
  - Finish[i] == false
  - Need[i] ≤ Work
Do:
  - Work = Work + Allocation[i]
  - Finish[i] = true

If Finish[i] == true for all i:
  State is safe
Else:
  State is unsafe
```

### Resource Allocation Graph (RAG) Method

**Use case**: Systems with single instances of each resource type

#### Key Features
- **Claim edges** (dashed): Indicate potential future requests
- **Request edges**: Active resource requests  
- **Assignment edges**: Currently allocated resources

#### Rule
- State is unsafe ⟺ RAG contains a cycle
- Grant requests only if no cycles form after allocation

### Deadlock Detection Algorithm

**Purpose**: Detect existing deadlocks

**Similarity**: Like Banker's algorithm but uses current requests instead of maximum needs

**Complexity**: O(mn²)

#### Algorithm
```
Work = Available
Finish[i] = (Allocation[i] == 0) for all i

While there exists i such that:
  - Finish[i] == false  
  - Request[i] ≤ Work
Do:
  - Work = Work + Allocation[i]
  - Finish[i] = true

If Finish[i] == false for some i:
  System is deadlocked (processes with Finish[i] == false are deadlocked)
```

## Deadlock Recovery

When deadlock is detected, recovery options include:

### 1. Process Termination
- Kill deadlocked processes
- Selection criteria: priority, computation time, resources held, etc.

### 2. Resource Preemption  
- Forcibly reclaim resources from some processes
- May not be feasible for all resource types
- Requires rollback mechanisms

## Practical Considerations

### Performance Trade-offs
- **Deadlock Prevention**: Most practical approach
- **Deadlock Avoidance**: High runtime overhead (not practical)
- **Deadlock Detection**: Expensive + timing issues

### Kernel vs Application Deadlocks

#### Application-level Deadlocks
- User process resource requests (file locks, exclusive device access)
- Considered application responsibility
- Kernel provides no deadlock guarantees

#### Kernel-level Deadlocks  
- Kernel locks and synchronization resources
- Kernel responsibility to prevent
- Usually handled via deadlock prevention techniques

### Detection Frequency Dilemma
- **Too frequent**: High overhead
- **Too infrequent**: Resource wastage from undetected deadlocks

## Summary

| Approach | Overhead | Practicality | When to Use |
|----------|----------|--------------|-------------|
| Prevention | Low | High | Most systems |
| Avoidance | High | Low | Special cases |
| Detection & Recovery | Medium | Medium | Batch systems |

**Recommendation**: Deadlock prevention is typically the most practical approach for real-world operating systems.
