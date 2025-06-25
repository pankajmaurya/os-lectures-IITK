# Operating Systems Lecture 7 - Context Switching
Also see https://linux-kernel-labs.github.io/refs/heads/master/lectures/processes.html

## Course Information
- **Course**: CS330 - Operating Systems
- **Institution**: IIT Kanpur
- **Topic**: Context Switch from Process to Process

## Overview

Context switching is a fundamental operating system mechanism that enables multitasking by allowing the CPU to switch execution from one process to another. This lecture covers the technical details of how context switching is implemented at the system level.

## Key Concepts

### What is Context Switching?

Context switching involves:
1. **Saving the state** of the currently running process
2. **Loading the saved state** of the new process to be executed

### Major Components of Process State

The process state that needs to be switched consists of two main components:

#### 1. Address Translation Tables
- Usually kept in memory at all times
- Switching involves changing a special CPU register that points to the address translation tables
- The pointer value is obtained from the Process Control Block (PCB) of the new process
- No immediate effect since kernel execution continues with kernel mappings

#### 2. CPU Register Values
- All CPU register values must be saved and restored
- Handled by an assembly-coded switch routine
- Current process registers → saved to PCB
- New process registers → restored from PCB

## The Context Switch Process

### Step-by-Step Execution

1. **Address Translation Setup**
   - Update CPU register to point to new process's address translation tables
   - Kernel code/data remains mapped consistently across all processes

2. **Register State Management**
   - Assembly switch routine saves all current register values to current process PCB
   - Same routine restores register values from new process PCB
   - Stack pointer restoration effectively switches to new process's stack

3. **Process Control Update**
   - Update `current` variable to point to new process's PCB

### Important Technical Details

- **Kernel vs User State**: When a process enters the kernel (via interrupt/trap), its user-level CPU state is initially saved, but the process continues executing in kernel mode with different CPU state
- **State to Save**: The CPU state that must be saved during context switch is the kernel-mode execution state, not the original user-mode state
- **Stack Management**: Stack content doesn't need explicit saving (already in memory), but stack pointer register value must be saved/restored

## Memory Architecture

### Stack Organization

Each process maintains two separate stacks:

#### User Stack
- Used during user-mode execution
- Process-specific memory space

#### Kernel Stack
- Used during kernel-mode execution
- Fixed size allocated at process creation
- Stack pointer switched immediately upon kernel entry
- Previous stack pointer value saved to kernel stack

### Address Space Layout

- Kernel code and data mapped to same virtual address space location for all processes
- Protection mechanisms ensure kernel space only accessible in supervisor mode
- Address translation switching has no immediate effect on kernel execution

## Process Control Block (PCB) - Detailed Analysis

### What is a Process Control Block?

A Process Control Block (PCB) is a data structure that is used by an Operating System to manage and regulate how processes are carried out. The PCB is created when a process is initialized and serves as the process's "identity card" in the operating system.

### PCB Structure and Components

The PCB contains comprehensive information about each process, organized into several key categories:

#### 1. Process Identification Information
- **Process ID (PID)**: The OS assigns a unique identifier to every process as soon as it is created which is known as Process ID, this helps to distinguish between processes.
- **Parent Process ID (PPID)**: Identifier of the process that created this process
- **User ID**: Owner of the process

#### 2. Process State Information
- **Process State**: The state of the process is stored in the PCB which helps to manage the processes and schedule them. There are different states for a process which are "running," "waiting," "ready," or "terminated."
- **Program Counter**: While running processes when the context switch occurs the last instruction to be executed is stored in the program counter which helps in resuming the execution of the process from where it left off.
- **CPU Registers**: The CPU registers of the process helps to restore the state of the process so the PCB stores a copy of them.

#### 3. Process Control Information
- **Priority Level**: Process scheduling priority
- **Scheduling Algorithm**: Information about which scheduling algorithm applies
- **Process Flags**: Various control flags for process management
- **Quantum/Time Slice**: Allocated CPU time for round-robin scheduling

#### 4. Memory Management Information
- **Base Address**: Starting address of process memory
- **Limit Register**: Memory boundaries for protection
- **Page Tables**: Virtual memory management structures
- **Segment Tables**: For segmented memory systems
- **Memory Usage**: The information like the base address or total memory allocated to a process is stored in PCB which helps in efficient memory allocation to the processes.

#### 5. I/O and Resource Information
- **Open File Descriptors**: List of files currently opened by the process
- **I/O Device Allocation**: Devices assigned to the process
- **Resource Usage**: Current resource consumption
- **Pending I/O Requests**: Outstanding I/O operations

#### 6. Accounting Information
- **CPU Time Used**: Total processor time consumed
- **Real Time Used**: Wall-clock time since process creation
- **Time Limits**: Maximum allowed execution time
- **Memory Usage Statistics**: Peak and current memory consumption
- **I/O Statistics**: Number of read/write operations performed

### PCB Storage and Location

The Process Control Block (PCB) is stored in a special part of memory that normal users can't access. This is because it holds important information about the process. Some operating systems place the PCB at the start of the kernel stack for the process, as this is a safe and secure spot.

#### Storage Methods
1. **Fixed Location**: PCBs stored in a reserved kernel memory area
2. **Kernel Stack**: PCB placed at the beginning of each process's kernel stack
3. **Process Table**: Array of PCBs indexed by process ID
4. **Linked List**: PCBs are stored in the form of LinkedList in the memory.

### PCB Operations in Context Switching

During context switching, the PCB plays several critical roles:

#### Save Operation
1. **Register State**: All CPU register values saved to current process PCB
2. **Program Counter**: Current instruction pointer preserved
3. **Stack Pointer**: Current stack position recorded
4. **Processor Flags**: Condition codes and status flags saved

#### Restore Operation
1. **Memory Context**: Address translation tables switched
2. **Register State**: New process register values loaded from PCB
3. **Stack Context**: Stack pointer restored to new process stack
4. **Execution Resume**: Program counter set to continue execution

### Process Table Organization

The process table is an array of PCBs, which logically contains a PCB for all of the current processes in the system. This organization enables:

- **Fast Process Lookup**: Direct indexing by Process ID
- **Process Enumeration**: Easy iteration through all processes
- **Resource Management**: Centralized view of system resource usage
- **Scheduling Decisions**: Quick access to scheduling information

### PCB-Enabled Operating System Functions

#### 1. Process Scheduling
The different information like Process priority, process state, and resources used can be used by the OS to schedule the process on the execution stack.

#### 2. Multitasking Support
Resource allocation, process scheduling, and process synchronization altogether helps the OS to multitask and run different processes simultaneously.

#### 3. Context Switching
When context switching happens in the OS the process state is saved in the CPU register and a copy of it is stored in the PCB. When the CPU switches to another process and then switches back to that process the CPU fetches that value from the PCB and restores the previous state of the process.

#### 4. Resource Sharing
The PCB stores information like the resources that a process is using, such as files open and memory allocated. This information helps the OS to let a new process use the resources which are being used by any other process to execute sharing of the resources.

### Advantages of PCB

PCB stores all the information about the process so it lets the operating system execute different tasks like process scheduling, context switching, etc.

Key benefits include:
- **Efficient Scheduling**: CPU resources allocated optimally
- **State Preservation**: Complete process state maintained across context switches
- **Resource Management**: Efficient utilization and sharing of system resources
- **Process Synchronization**: Coordination between multiple processes
- **System Stability**: Organized process management prevents conflicts

### Disadvantages and Overhead

To store the PCB for each and every process there is a significant usage of the memory in there can be a large number of processes available simultaneously in the OS.

Challenges include:
- **Memory Overhead**: Each PCB consumes kernel memory
- **Complexity**: Increased system complexity for PCB management
- **Performance Impact**: PCB maintenance operations consume CPU cycles
- **Scalability**: Large numbers of processes require extensive PCB management

### PCB Security Considerations

- **Kernel Protection**: PCBs stored in protected kernel memory space
- **Access Control**: Only kernel-mode code can modify PCBs
- **Integrity Checks**: Critical for system security and stability
- **Isolation**: Process information kept separate to prevent interference

## CPU Switch Mechanism

```
Process A (running) → Context Switch → Process B (running)
     ↓                    ↑                    ↑
   Save state         Switch routine      Restore state
     ↓                    ↑                    ↑
   PCB-A              Assembly code         PCB-B
```

## Visual Diagrams

### PCB Structure Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                    PROCESS CONTROL BLOCK                    │
├─────────────────────────────────────────────────────────────┤
│ PROCESS IDENTIFICATION                                      │
│ ┌─────────────────┬─────────────────┬─────────────────────┐ │
│ │ Process ID (PID)│ Parent PID      │ User ID             │ │
│ │ 1234            │ 567             │ user123             │ │
│ └─────────────────┴─────────────────┴─────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ PROCESSOR STATE INFORMATION                                 │
│ ┌─────────────────┬─────────────────┬─────────────────────┐ │
│ │ Process State   │ Program Counter │ Stack Pointer       │ │
│ │ READY           │ 0x8048000       │ 0x7FFF1234          │ │
│ └─────────────────┴─────────────────┴─────────────────────┘ │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ CPU REGISTERS                                           │ │
│ │ EAX: 0x12345678  EBX: 0x87654321  ECX: 0xABCDEF00       │ │
│ │ EDX: 0x11223344  ESI: 0x55667788  EDI: 0x99AABBCC       │ │
│ │ Flags: 0x0246    ... (more registers)                   │ │
│ └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ PROCESS CONTROL INFORMATION                                 │
│ ┌─────────────────┬─────────────────┬─────────────────────┐ │
│ │ Priority        │ Scheduling Algo │ Time Quantum        │ │
│ │ HIGH (10)       │ Round Robin     │ 50ms                │ │
│ └─────────────────┴─────────────────┴─────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ MEMORY MANAGEMENT INFORMATION                               │
│ ┌─────────────────┬─────────────────┬─────────────────────┐ │
│ │ Base Address    │ Limit           │ Page Table Ptr      │ │
│ │ 0x00400000      │ 1MB             │ 0xC0000000          │ │
│ └─────────────────┴─────────────────┴─────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ I/O & RESOURCE INFORMATION                                  │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ Open Files: [fd0: stdin, fd1: stdout, fd3: data.txt]    │ │
│ │ Allocated Resources: [Printer-1, Network-Socket-443]    │ │
│ └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ ACCOUNTING INFORMATION                                      │
│ ┌─────────────────┬─────────────────┬─────────────────────┐ │
│ │ CPU Time Used   │ Memory Usage    │ I/O Operations      │ │
│ │ 2.5 seconds     │ 512KB           │ 1,250 ops           │ │
│ └─────────────────┴─────────────────┴─────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

### Context Switch Flow Diagram

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Process A     │    │   OS Kernel     │    │   Process B     │
│   (Running)     │    │   (Scheduler)   │    │   (Ready)       │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         │ 1. Interrupt/         │                       │
         │    System Call        │                       │
         ├──────────────────────►│                       │
         │                       │                       │
         │ 2. Save Process A     │                       │
         │    State to PCB-A     │                       │
         │◄──────────────────────┤                       │
         │                       │                       │
         │                       │ 3. Select Process B   │
         │                       │    for execution      │
         │                       ├──────────────────────►│
         │                       │                       │
         │                       │ 4. Load Process B     │
         │                       │    State from PCB-B   │
         │                       │◄──────────────────────┤
         │                       │                       │
         │ 5. Process A          │ 6. Switch to          │ 7. Process B
         │    suspended          │    Process B          │    running
         │    (in PCB-A)         │    context            │    (from PCB-B)
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Process A     │    │   Context       │    │   Process B     │
│   (Suspended)   │    │   Switched      │    │   (Running)     │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### Process State Transition Diagram

```
        ┌─────────────┐
        │     NEW     │
        │  (Created)  │
        └─────────────┘
               │
               │ Admit
               ▼
        ┌─────────────┐           ┌─────────────┐
        │    READY    │◄─────────►│   RUNNING   │
        │ (In Queue)  │  Dispatch │ (Executing) │
        └─────────────┘           └─────────────┘
               ▲                         │
               │                         │
               │ I/O Complete           │ I/O Request
               │ or Event               │ or Event Wait
               │                         ▼
        ┌─────────────┐           ┌─────────────┐
        │   WAITING   │           │ TERMINATED  │
        │ (Blocked)   │           │  (Ended)    │
        └─────────────┘           └─────────────┘
```

### Memory Layout During Context Switch

```
┌─────────────────────────────────────────────────────────────┐
│                    PHYSICAL MEMORY                          │
├─────────────────────────────────────────────────────────────┤
│ KERNEL SPACE (Protected)                                    │
│ ┌─────────────┬─────────────┬─────────────┬─────────────┐   │
│ │   PCB-A     │   PCB-B     │   PCB-C     │    ...      │   │
│ │ (Saved)     │ (Active)    │ (Saved)     │             │   │
│ └─────────────┴─────────────┴─────────────┴─────────────┘   │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ Process Table (Array of PCB Pointers)                   │ │
│ │ [0] → PCB-A  [1] → PCB-B  [2] → PCB-C  ...              │ │
│ └─────────────────────────────────────────────────────────┘ │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ Kernel Stack Area                                       │ │
│ │ Stack-A │ Stack-B │ Stack-C │ ...                       │ │
│ └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ USER SPACE (Process Virtual Memory)                         │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ Process B Address Space (Currently Active)              │ │
│ │ ┌─────────┬─────────┬─────────┬─────────┬─────────────┐ │ │
│ │ │  Code   │  Data   │  Heap   │ Stack   │   Unused    │ │ │
│ │ └─────────┴─────────┴─────────┴─────────┴─────────────┘ │ │
│ └─────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

### PCB Lifecycle Diagram

```
Process Creation → PCB Creation → Process Execution → Context Switches → Process Termination
       │                │                │                    │                   │
       ▼                ▼                ▼                    ▼                   ▼
┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐
│   fork()    │  │ Allocate    │  │ CPU assigns │  │ Save/Restore│  │ Deallocate  │
│   exec()    │  │ PCB memory  │  │ to process  │  │ PCB state   │  │ PCB memory  │
│   CreateProc│  │ Initialize  │  │ Load from   │  │ Update      │  │ Remove from │
│             │  │ fields      │  │ PCB         │  │ statistics  │  │ Process     │
│             │  │ Add to      │  │             │  │             │  │ Table       │
│             │  │ Process     │  │             │  │             │  │             │
│             │  │ Table       │  │             │  │             │  │             │
└─────────────┘  └─────────────┘  └─────────────┘  └─────────────┘  └─────────────┘
```

## Key Takeaways

1. **Efficiency**: Context switching is optimized by keeping address translation tables in memory
2. **Assembly Implementation**: Low-level register manipulation requires assembly code
3. **Stack Management**: Separate user/kernel stacks enable secure mode transitions
4. **State Preservation**: Complete CPU state must be preserved to resume processes correctly
5. **Atomicity**: The switch routine executes atomically to maintain system consistency

## Technical Implementation Notes

- Context switch occurs within kernel mode
- Switch routine returns in the context of the NEW process
- Memory protection ensures kernel space security
- Fixed kernel stack sizes simplify memory management

---

*This README summarizes the key concepts from Operating Systems Lecture 7 covering process context switching mechanisms and implementation details.*
