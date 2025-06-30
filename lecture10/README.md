# Unix Unnamed Pipes - Operating Systems Lecture 10

This document covers **unnamed pipes** in Unix/Linux operating systems, focusing on inter-process communication (IPC) mechanisms.

## Table of Contents
- [Overview](#overview)
- [Technical Characteristics](#technical-characteristics)
- [System Implementation](#system-implementation)
- [I/O Redirection Mechanism](#io-redirection-mechanism)
- [Code Examples](#code-examples)
- [Key Takeaways](#key-takeaways)

## Overview

Unnamed pipes are a fundamental IPC mechanism that enables communication between **related processes** such as:
- Parent-child processes
- Sibling processes

> **Important**: Access to unnamed pipes can only be obtained through inheritance. There's no way to access an existing unnamed pipe from an unrelated process.

## Technical Characteristics

### FIFO Buffer
- Each pipe has a **fixed-size buffer**
- Operates as a **first-in, first-out (FIFO) queue**
- Stores **bytes**, not messages (message boundaries are not preserved)

### Multiple Readers/Writers
- A single pipe can have multiple readers and/or writers
- Data written by writers is queued in FIFO order
- Each byte is read only once - two readers will never get the same data

### Blocking Behavior
- **Read operations**: Block until data is available in the buffer
- **Write operations**: Block only when the buffer is full
- **Partial reads**: Read requests return as soon as any data is available (may be less than requested)

## System Implementation

### Creating Pipes
```c
int pipe(int fd[2]);
```
- **Parameter**: Pointer to an array of at least 2 integers
- **Return**: 0 on success, -1 on failure
- **Result**: 
  - `fd[0]` = file descriptor for reading
  - `fd[1]` = file descriptor for writing

### Reading/Writing
Uses standard file I/O system calls:
- `read(fd[0], buffer, n)` - Read from pipe
- `write(fd[1], buffer, n)` - Write to pipe

## I/O Redirection Mechanism

### File Descriptor Tables
- Each process maintains an **open file descriptor table**
- File descriptors are indices into this table
- During `fork()`, child inherits a copy of parent's table

### Standard Streams
| File Descriptor | Stream | Purpose |
|-----------------|--------|---------|
| 0 | stdin | Standard input |
| 1 | stdout | Standard output |
| 2 | stderr | Standard error |

### dup() System Call
- Duplicates a file descriptor to the first unused entry
- Key mechanism for implementing I/O redirection
- Process can redirect stdout by closing fd 1 and duping desired fd

## Code Examples

### Basic Parent-Child Communication
```c
int r, fd[2], cpid;

r = pipe(fd);

if (r == -1) {
    ...error...
}

switch (cpid = fork()) {
    case -1:
        ...error...
    
    case 0:  /* child */
        close(fd[0]); 
        /* child does not wish to read from pipe,
           so it closes the file descriptor for reading the pipe
        */
        r = write(fd[1], buffer, n);
        ....
    
    default: /* parent */
        close(fd[1]);
        r = read(fd[0], buffer, n);
        ....
}
....
```

### Shell Command Piping (`ls -l | more`)
```c
int cpid1, cpid2, r, fd[2];

// Create pipe
r = pipe(fd);
if (r == -1) { 
    // Handle error
}

// First child (ls command)
switch (cpid1 = fork()) {
    case 0: 
        close(fd[0]);     // Won't read from pipe
        close(1);         // Close stdout
        dup(fd[1]);       // Redirect stdout to pipe
        close(fd[1]);     // Close original pipe fd
        execve("/bin/ls", ...);
        break;
}

// Second child (more command)
switch (cpid2 = fork()) {
    case 0: 
        close(fd[1]);     // Won't write to pipe
        close(0);         // Close stdin
        dup(fd[0]);       // Redirect stdin from pipe
        close(fd[0]);     // Close original pipe fd
        execve("/usr/bin/more", ...);
        break;
}

// Parent (shell)
close(fd[0]); 
close(fd[1]);    // Close both ends
wait(...); 
wait(...);       // Wait for both children
```

## Key Takeaways

1. **Inheritance-based Access**: Only related processes can communicate via unnamed pipes
2. **Byte Stream**: Pipes handle bytes, not discrete messages
3. **FIFO Ordering**: Data maintains first-in, first-out order
4. **File Descriptor Management**: Proper closing of unused file descriptors is crucial
5. **I/O Redirection**: Foundation for shell piping and redirection mechanisms
6. **Process Synchronization**: Read/write blocking provides natural synchronization

## Use Cases

- **Shell Command Piping**: `command1 | command2`
- **Parent-Child Communication**: Data passing between related processes
- **Producer-Consumer Patterns**: One process generates data, another consumes it
- **Filter Chains**: Sequential data processing through multiple stages

---

*This material is based on CS330 Operating Systems lecture notes from IIT Kanpur.*
