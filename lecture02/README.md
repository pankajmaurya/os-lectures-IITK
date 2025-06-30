# Lecture 2: Review of I/O Hardware
See https://claude.ai/public/artifacts/f0cbf51a-0486-4f15-b4c6-3e57b3c4dd65

## Overview
This lecture covers the fundamental concepts of I/O hardware organization and interrupt handling mechanisms in operating systems.

## Key Topics

### I/O Device Architecture
- I/O devices connect to computers through **device controllers** attached to the system bus
- Device controllers contain control registers and buffers accessible by the CPU
- CPU initiates I/O by writing to controller registers and buffers

### Device Access Methods
- **Memory-mapped I/O**: Device registers appear as memory addresses
- **I/O-mapped I/O**: Separate address space for I/O operations
- Both methods can be used simultaneously for the same device

### I/O Completion Detection
Since I/O operations are asynchronous, the CPU uses two methods to detect completion:
- **Polling**: CPU repeatedly checks device status
- **Interrupts**: Device signals completion to CPU (preferred method)

### Interrupt Handling System
- **Interrupt lines**: Shared communication channel between devices and CPU
- **Daisy chaining**: Multiple devices sharing single interrupt line
- **Vectored interrupts**: Dedicated interrupt controller for efficient source identification
- **Interrupt priorities**: Higher priority interrupts can preempt lower priority ones

### Interrupt Processing Flow
1. CPU automatically saves critical registers (program counter, status word)
2. Jump to interrupt service routine based on interrupt vector
3. Service routine saves additional registers it will modify
4. Perform necessary I/O operations and device management
5. Restore all saved registers
6. Return to original program execution using special instruction (IRET)

User to kernel stack switch
```mermaid
sequenceDiagram
    participant UserApp as User Space<br>(Ring 3)
    participant CPU as CPU
    participant TSS as Task State Segment (TSS)
    participant KernelStack as Kernel Stack (RSP0)

    UserApp->>CPU: Triggers interrupt or syscall<br>(e.g., `int 0x80`, `syscall`)
    CPU->>TSS: Checks privilege level (Ring 3 → Ring 0)
    TSS-->>CPU: Provides `RSP0` (kernel stack address)
    CPU->>KernelStack: Switches from user `RSP` to `RSP0`
    CPU->>KernelStack: Pushes SS, RSP (old user stack)
    CPU->>KernelStack: Pushes RFLAGS, CS, RIP
    CPU->>KernelStack: Starts executing ISR in kernel
```

```markdown
High Memory Address (RSP0 from TSS) ← Stack pointer before CPU pushes
---------------------------------------------------------
| RIP       | ← Pushed first by CPU
| CS        |
| RFLAGS    |
| RSP       | ← Only on CPL change (user → kernel)
| SS        | ← Only on CPL change
| RCX       | ← Pushed by ISR
| RBX       |
| RAX       |
---------------------------------------------------------
Low Memory Address (Current RSP after ISR saves registers) = Top of Stack
```

```mermaid
graph TD
    high[High Memory Address]
    rsp0[RSP0 from TSS<br>← Loaded by CPU on interrupt]
    rip[RIP user ← Pushed by CPU]
    cs[CS user ← Pushed by CPU]
    rflags[RFLAGS ← Pushed by CPU]
    ursp[RSP user ← Pushed by CPU]
    ss[SS user ← Pushed by CPU]
    rcx[RCX ← Saved by ISR]
    rbx[RBX ← Saved by ISR]
    rax[RAX ← Saved by ISR]
    final_rsp[Final RSP points here<br>← Top of kernel stack after pushes]
    low[Low Memory Address]

    high --> rsp0 --> rip --> cs --> rflags --> ursp --> ss --> rcx --> rbx --> rax --> final_rsp --> low
```

The following Mermaid diagram visualizes what happens when `IRETQ` is executed:

```mermaid
flowchart TD
    Start([Interrupt Handler Complete])
    IRETQ["CPU executes IRETQ"]
    PopRIP["Pop RIP (return address) from stack"]
    PopCS["Pop CS (code segment) from stack"]
    PopRFLAGS["Pop RFLAGS (status flags) from stack"]
    CheckPL["Is this a privilege level change? (e.g., Ring 0 → Ring 3)"]
    PopSS["Pop SS (stack segment) from stack"]
    PopRSP["Pop RSP (user stack pointer) from stack"]
    SecurityCheck["CPU performs privilege checks (CS, SS, stack)"]
    Resume(["Resume user-mode execution at RIP with restored RFLAGS"])

    Start --> IRETQ
    IRETQ --> PopRIP
    PopRIP --> PopCS
    PopCS --> PopRFLAGS
    PopRFLAGS --> CheckPL
    CheckPL -->|Yes| PopSS
    PopSS --> PopRSP
    PopRSP --> SecurityCheck
    SecurityCheck --> Resume
    CheckPL -->|No| Resume
```
Comparison between RET and IRET:
```markdown
| Feature                | `RET`                  | `IRET`                                          |
| ---------------------- | ---------------------- | ----------------------------------------------- |
| Used for               | Normal function return | Interrupt/exception return                      |
| Pops                   | Just `RIP`/`EIP`       | `RIP`, `CS`, `RFLAGS`, (optionally `SS`, `RSP`) |
| Handles Ring Changes   | ❌ No                   | ✅ Yes                                           |
| Re-enables interrupts? | ❌ No                   | ✅ If IF flag was set                            |
```

### Important Concepts
- **Interrupt transparency**: Interrupt handling must be invisible to running programs
- **Interrupt masking**: Lower priority interrupts can be temporarily disabled
- **Traps**: Software-generated interrupts used for system calls
- **Synchronous vs Asynchronous**: Exceptions and traps are synchronous with program execution, unlike hardware interrupts

### Best Practices
- Interrupts should not be disabled for extended periods to avoid losing signals
- Proper state saving and restoration ensures program transparency
- Interrupt controllers improve efficiency in multi-device systems
