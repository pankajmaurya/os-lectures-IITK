# Operating Systems (CS330) - Lecture 9

## Process Termination and Inter-Process Communication

### Table of Contents
- [Process Termination](#process-termination)
- [Unix Process Hierarchy](#unix-process-hierarchy)
- [Inter-Process Communication (IPC)](#inter-process-communication-ipc)
  - [Message Passing](#message-passing)
  - [Shared Memory](#shared-memory)
- [IPC Design Considerations](#ipc-design-considerations)

---

## Process Termination

When a process calls the `exit` system call, the following cleanup occurs:

- **Resource Release**: Most resources held by the process are released
  - All physical memory allocated to the process is freed
  - Address translation tables are deallocated
  - All open files are closed

- **Process Control Block**: Minimal information is retained including:
  - Exit status
  - Resource usage information

- **Zombie State**: The process enters the Zombie state and calls the scheduler to give up CPU

### Signal Termination
A process may also terminate due to signal receipt (covered in detail in later lectures).

### Wait System Call
The `wait` system call returns a status word that encodes:
- How the child terminated (exit call or signal receipt)
- Exit status or the signal that caused termination

Decoding macros are available for interpreting this information. Additional system calls like `wait3` and `wait4` allow waiting for specific child processes.

---

## Unix Process Hierarchy

### Boot Process and Init Handcrafting

#### How the Kernel "Handcrafts" Init

The term "handcraft" refers to the unique way the kernel creates the init process, bypassing normal process creation mechanisms:

**1. Initial Setup**
- Kernel starts with a statically allocated task structure (`INIT_TASK`) representing the initial kernel thread (PID 0)
- Uses `kernel_thread()` function instead of normal `fork()` system call

**2. Special Creation Process**
```
Kernel Space:
kernel_thread() → kernel_init() function → waits for subsystems
                                      ↓
                                 transitions to user space
                                      ↓
                                 exec("/sbin/init")
```

**3. Unique Characteristics**
- **No Parent**: Init has PID=1 and PPID=0 (no meaningful parent)
- **Direct Kernel Creation**: Created by kernel itself, not by another process
- **Manual PID Assignment**: Kernel directly assigns PID 1
- **Ancestor Role**: All user processes descend from init

**4. Why "Handcrafted"?**
- Only process not born from another process via `fork()`
- Kernel manually sets up process control block, memory space, and execution context
- Establishes foundation for entire process hierarchy
- Serves as parent for orphaned processes

**5. Boot Flow**
1. **Kernel Initialization**: Kernel performs system initialization
2. **Init Handcrafting**: Kernel creates init process using special mechanism
3. **Getty Processes**: `init` creates `getty` processes for each terminal

### Login Process Flow
```
init → forks → getty → prints login prompt
                ↓
              waits for login name
                ↓
              execs login program → reads password → authenticates
                ↓
              execs user's login shell
```

### Process Management
- The login shell process is a child of the `init` process
- When the shell process exits, `init` creates another `getty` process for the terminal
- The kernel makes `init` the parent of any orphaned processes
- Since `init` continuously waits for child processes to die, no process remains zombie forever

---

## Inter-Process Communication (IPC)

Applications with multiple cooperating processes require facilities for:
- **Communication**: Data sharing between processes
- **Synchronization**: Coordination of activities among processes

Operating systems provide two main IPC mechanisms:

### Message Passing

**Characteristics:**
- Processes send arbitrary messages to each other
- Achieves both communication and synchronization simultaneously
- Message receipt indicates something about the sender's state

**Communication Types:**

#### Direct Communication
- No explicit link establishment required
- Sender directly names the target process (using PID, etc.)
- Inflexible and not commonly used

#### Indirect Communication
- Link must be explicitly established first
- Link may be called: channel, mailbox, port, or message queue
- Kernel allocates buffer to store sent but undelivered messages
- Both sender and receiver specify the link rather than process identity

**Link Establishment Methods:**

1. **Named Links**
   - Link given a name known to both processes
   - Second process requests OS access to named link
   - Requires read/write permissions
   - Examples: Unix named pipes, System V message queues (`msgget` system call)

2. **Inherited Links**
   - Used between related processes (parent-child relationship)
   - One process creates link, then creates second process
   - Second process inherits link access
   - No permissions needed since only related processes communicate
   - Example: Unix unnamed pipes

### Shared Memory

**Characteristics:**
- Two or more processes share parts of their virtual address spaces
- Same physical memory area mapped to multiple process address spaces
- Changes made by one process are visible to all sharing processes
- Requires additional synchronization primitives to prevent inconsistencies

**Implementation:**
- Originally implemented in System V Unix
- Now available in most Unix flavors including Linux
- Uses `shmget` system call for setup

**Synchronization Challenges:**
- Multiple processes may attempt to write different values to the same memory location simultaneously
- Requires careful coordination (covered in detail with threads topic)

---

## IPC Design Considerations

### Higher-Level Abstractions
- **Remote Procedure Calls (RPC)**
- **Remote Object Calls** (e.g., RMI in Java)
- Built upon message passing primitives

### Message Passing Design Issues

#### Blocking vs Non-Blocking Calls
- **Send Calls**: Typically non-blocking (asynchronous) unless buffer is full
- **Receive Calls**: Typically blocking (synchronous) until message is available

#### Message Boundaries
- **Preserved**: Receiver gets sequence of demarcated messages
  - Example: Message queues
- **Not Preserved**: Receiver gets stream of bytes
  - Example: Unix pipes (named and unnamed)

---

## Key System Calls and Concepts

| System Call | Purpose |
|-------------|---------|
| `exit` | Process termination |
| `wait` | Parent waits for child termination |
| `wait3`, `wait4` | Wait for specific child processes |
| `shmget` | Shared memory setup |
| `msgget` | System V message queue setup |

## Related Topics
- Signals (detailed in later lectures)
- Thread synchronization
- Unix pipes (detailed in next lecture)

---

*This README summarizes key concepts from Operating Systems (CS330) Lecture 9 covering process termination and inter-process communication mechanisms.*
