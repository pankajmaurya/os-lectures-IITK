# Operating Systems (CS330) - Lecture 24
## Real-Time Systems and Multiprocessor Scheduling

### Overview
This lecture covers real-time system scheduling and multiprocessor scheduling concepts in operating systems.

---

## Real-Time Systems

### Definition and Characteristics
- **Real-time system**: A system where responses to inputs must be produced within specified time limits (deadlines)
- Outputs must be both **correct** and **timely**
- Widely used in safety-critical control applications
- Typically employ dedicated embedded systems

### Classification
- **Hard real-time systems**: Critical to meet deadlines
- **Soft real-time systems**: Less critical deadline requirements

### Real-Time Application Structure
- Consists of multiple processes/threads
- Each has specific deadline and processing time requirements
- Scheduling strategy must ensure all processes meet their deadlines

---

## Real-Time Scheduling

### Static Priority Assignment
- **Most common approach**: Assign static priorities to real-time processes
- Real-time process priorities > maximum priority of non-real-time processes
- Static priorities don't change based on CPU usage or other characteristics

### Rate Monotonic Scheduling
- **Key principle**: Higher priorities assigned to processes with smaller (tighter) deadlines
- **Proven optimal** for static priority assignment
- Celebrated result in real-time scheduling theory

### Solaris Implementation
- Supports real-time process class
- Uses `priocntl` system call to set scheduling class and priority
- Preemptible kernel ensures bounded dispatch latency
- Higher priority processes immediately preempt lower priority ones

---

## Priority Inheritance

### The Problem
- **Priority inversion**: High-priority processes blocked by lower-priority processes holding shared resources
- Can lead to unbounded blocking times
- Example: P1 (high) waits for resource L held by P3 (low), while P2 (medium) preempts P3

### Solution: Priority Inheritance Protocol
- Lower-priority process "inherits" higher priority while holding critical resource
- Ensures bounded blocking times
- Multiple protocols exist with different inheritance strategies

### Example Implementation
- When P1 blocks for resource L held by P3, P3 inherits P1's priority
- P2 cannot preempt P3 during critical section
- Worst-case blocking time = duration of P3's critical section

---

## Multiprocessor Scheduling

### SMP (Symmetric Multiprocessing) Approach
- **Single shared ready queue** accessed by all processors
- Independent scheduling on each processor
- Most eligible process selected per scheduling algorithm
- Requires synchronized access to ready queue

### Advantages
- **Automatic load balancing**: No processor idle while runnable processes exist
- Minimal changes to uniprocessor scheduling algorithms

### Processor Affinity
- **Concept**: Preference for processes to run on same processor as last execution
- **Benefit**: Maintains "warm cache" for better performance
- Slight modification to existing scheduling strategies

### Processor Binding
- **Feature**: Available in Linux, Solaris
- Threads can be bound to specific processors or processor subsets
- **Use case**: Compute-intensive parallel applications
- Helps achieve optimal performance in specialized scenarios

---

## Scheduling Algorithm Evaluation

### Selection Challenges
- Multiple algorithms with various parameters
- Difficult to choose optimal solution
- Requires clear criteria definition (CPU utilization, response time, throughput)

### Evaluation Methods

#### 1. Deterministic Analytic Evaluation
- **Approach**: Calculate performance measures for known process sets
- **Limitation**: Results don't generalize
- **Use**: Understanding algorithm behavior only

#### 2. Queuing Model Approach
- **Method**: Assumes known arrival patterns and service time distributions
- **Analysis**: Analytical computation of average performance measures
- **Constraint**: Limited to specific probability distributions and scheduling disciplines

#### 3. Simulation
- **Advantage**: Handles arbitrary probability distributions
- **Challenge**: No consensus on realistic user behavior models
- More flexible than analytical methods

#### 4. Implementation and Deployment
- **Method**: Actual OS implementation and user testing
- **Accuracy**: Most accurate evaluation approach
- **Drawback**: Expensive and time-consuming

---

## Key Takeaways

1. Real-time systems require guaranteed response times within deadlines
2. Rate monotonic scheduling is optimal for static priority assignment
3. Priority inheritance solves priority inversion problems
4. Multiprocessor scheduling benefits from shared queues and processor affinity
5. Algorithm evaluation requires careful consideration of multiple approaches
6. Practical implementation often provides the most accurate performance assessment

---

*Source: IIT Kanpur CS330 Operating Systems Course - Lecture 24*
