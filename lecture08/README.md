# Operating Systems (CS330) - Lecture 8: Process Creation

## Overview

This lecture covers the fundamental concepts of process creation in operating systems, with a focus on the Unix/Linux model of parent-child process relationships and the fork/exec mechanism.

## Table of Contents

- [Process Relationships](#process-relationships)
- [Process Creation Mechanisms](#process-creation-mechanisms)
- [The fork() System Call](#the-fork-system-call)
- [The execve() System Call](#the-execve-system-call)
- [Fork/Exec Model](#forkexec-model)
- [Copy-on-Write Optimization](#copy-on-write-optimization)
- [Advantages and Trade-offs](#advantages-and-trade-offs)

## Process Relationships

In Unix-like operating systems, processes are organized in a **parent-child hierarchy**:
- The **parent process** creates new processes through system calls
- The **child process** is the newly created process
- Children can create their own processes, forming a tree-like structure

## Process Creation Mechanisms

There are two main approaches to process creation:
1. **Single system call** - Creates and loads a new program in one step
2. **Fork/Exec model** - Separates process creation from program loading (Unix approach)

## The fork() System Call

### How fork() Works

When a process calls `fork()`, the kernel creates an identical child process:

- **Address space**: Child gets a duplicate of parent's memory
- **Register values**: All CPU registers are copied
- **Open files**: File descriptors are inherited
- **Program counter**: Child starts from the same execution point

### Return Values

The `fork()` system call returns different values to distinguish between processes:

| Process | Return Value | Meaning |
|---------|--------------|---------|
| Parent | Child's PID | Process ID of the newly created child |
| Child | 0 | Indicates this is the child process |
| Error | -1 | Process creation failed |

### Typical Usage Pattern

```c
switch(cpid = fork()) {
    case -1:
        /* ERROR - fork failed */
        break;
    case 0:
        /* Child process code */
        break;
    default:
        /* Parent process code */
        /* cpid contains child's PID */
        break;
}
```

## The execve() System Call

### Functionality

The `execve()` system call **replaces** the current process with a new program:

- Discards the existing virtual address space
- Creates new address space for the target program
- Loads code and initial data from the executable file
- **Does not return** if successful (process starts executing new program)

### Wrapper Functions

The C standard library provides multiple wrapper functions for `execve()`:
- `execl()`
- `execle()`
- `execvp()`
- And others...

All execute the same underlying `execve()` system call but accept arguments in different formats.

## Fork/Exec Model

### Common Usage Pattern

In practice, `fork()` is almost always immediately followed by `execve()` in the child process:

```c
// Example: Shell executing "ls" command
pid_t pid = fork();
if (pid == 0) {
    // Child process
    execve("/bin/ls", args, env);
} else if (pid > 0) {
    // Parent process continues
    wait(NULL); // Wait for child to complete
}
```

### Process Flow

1. Parent calls `fork()` → Child process created (identical to parent)
2. Child calls `execve()` → Child's memory replaced with new program
3. Child executes the new program
4. Parent continues its execution

## Copy-on-Write Optimization

### The Problem

Naive `fork()` implementation copies the entire address space, which is wasteful when immediately followed by `execve()`.

### The Solution: Copy-on-Write (COW)

1. **Initial State**: Parent and child share the same physical memory pages
2. **Memory Protection**: All writable areas marked as read-only for both processes
3. **Lazy Copying**: Physical copying only occurs when either process attempts to write
4. **Exception Handling**: Write attempts trigger exceptions, causing selective copying

### Benefits

- Reduces memory usage and creation time
- Only copies pages that are actually modified
- Optimizes the common fork/exec pattern

## Advantages and Trade-offs

### Advantages of Fork/Exec Model

1. **Flexibility**: Parent can manipulate child before `execve()`
   - Enables I/O redirection
   - Allows environment setup

2. **Same Program Execution**: Useful when parent and child run identical programs
   - Network servers
   - Parallel processing applications

3. **State Inheritance**: Child starts with copy of parent's state
   - Easy information passing
   - Shared context

### Trade-offs

- **Apparent Inefficiency**: Copying address space only to discard it
- **Mitigation**: Copy-on-write optimization addresses this concern
- **Synchronization**: In some implementations, parent suspended until child exits or calls `execve()`

## Implementation Notes

### Linux Specifics

- Linux provides `vfork()` system call
- `vfork()` functionality is identical to `fork()` in modern Linux
- Copy-on-write makes the distinction less relevant

### Memory Management

- Address translation tables duplicated from parent to child
- Physical memory sharing until write operations occur
- Exception-driven copying ensures data consistency

## Summary

The fork/exec model provides a powerful and flexible approach to process creation that:
- Separates process creation from program loading
- Enables sophisticated process manipulation
- Uses copy-on-write optimization for efficiency
- Forms the foundation of Unix-like process management

This model's design allows for complex behaviors like shell command execution, I/O redirection, and parallel processing while maintaining system efficiency through modern optimization techniques.
