# Dynamic Linking and Position Independent Code

## Overview
This lecture covers dynamic linking concepts, contrasting it with static linking discussed in the previous lecture. The focus is on understanding how dynamic linking works, its advantages and disadvantages, and the role of Position Independent Code (PIC).

## Dynamic Linking Fundamentals

### What is Dynamic Linking?
Dynamic linking defers the linking process until runtime, unlike static linking where library code becomes part of the binary. The program contains information about required libraries, and a dynamic linker handles loading and linking at runtime.

### Key Components
- **Dynamic Linker**: In UNIX systems, `ld.so` serves as the dynamic linker
- **Entry Point**: Program execution begins with a start function that passes control to the dynamic linker
- **Loading Mechanism**: Uses `mmap()` system call to map library code and data into process address space

## Advantages of Dynamic Linking

1. **Smaller Binary Files**: Executables are significantly smaller (example: 8.45 KB vs 2.08 MB for hello.c)
2. **Library Updates**: Programs don't need relinking to use newer library versions
3. **Runtime Loading**: Programs can load/unload routines during execution for better memory management
4. **Memory Sharing**: Library code in physical memory can be shared across processes

## Disadvantages of Dynamic Linking

1. **Performance Overhead**: Substantial runtime costs compared to static linking
2. **Version Conflicts**: Easy library updates can break existing programs expecting specific features
3. **Installation Issues**: Risk of installing older library versions over newer ones

## Memory Mapping with mmap()

### Function Prototype
```c
void * mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
```

### Key Parameters
- **Protection Flags**: `PROT_EXEC`, `PROT_READ`, `PROT_WRITE`, `PROT_NONE`
- **Mapping Flags**: 
  - `MAP_SHARED`: Changes visible to all processes
  - `MAP_PRIVATE`: Copy-on-write mapping
  - `MAP_FIXED`: Use specified address (discouraged)

## Runtime Relocation Challenges

### The Problem
- Static linker doesn't know where library code will be loaded
- Different programs may load libraries at different addresses
- Requires runtime relocation by dynamic linker
- Library code must be writable, preventing sharing

### Solutions: PLT and GOT

#### Procedure Linkage Table (PLT)
- Contains small code pieces for each library function
- Program calls redirect to PLT entries
- Implements lazy binding (resolve address on first call)

#### Global Offset Table (GOT)
- Data table containing actual addresses of library symbols
- PLT entries use indirect calls through GOT
- Initialized at dynamic linking time

## Position Independent Code (PIC)

### Purpose
Eliminates need for runtime relocation, enabling true code sharing across processes.

### How It Works
- Code determines its own address at runtime
- Uses relative addressing instead of absolute addresses
- Compiler generates special code with runtime address determination

### Example Mechanism
```assembly
f:  call NEXT        // relative call, pushes return address
NEXT: pop R1         // R1 now contains current instruction address
      call R1(DIFF)  // DIFF is offset to target function g()
```

### Benefits
- Multiple processes can share same library code in physical memory
- Substantial memory savings for commonly used libraries
- No runtime relocation required

## Memory Management for Variables

### Library Variables
- Space allocated in executable for library variables
- Program references point to executable's copy
- Prevents need for program code relocation
- Only library code requires runtime relocation (unless using PIC)

## Compilation for PIC
To generate position independent code:
```bash
gcc -O -fPIC -S -o output.s input.c
```

## Key Takeaways

1. Dynamic linking reduces binary sizes but adds runtime overhead
2. PLT/GOT mechanism enables efficient function calls without program relocation
3. Position Independent Code allows true library sharing across processes
4. Memory mapping (`mmap`) is fundamental to dynamic loading
5. Trade-offs exist between performance, memory usage, and flexibility
