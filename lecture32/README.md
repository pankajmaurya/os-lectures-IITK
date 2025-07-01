# Lecture 32 - Operating Systems (CS330)

## Overview
This lecture covers two main topics:
1. Position Independent Code (PIC) and Dynamic Linking
2. Introduction to File Systems

## Position Independent Code (PIC)

### Problem with Static Linking
- Each executable contains its own copy of libraries
- Causes memory waste when multiple programs use the same library simultaneously
- Each process loads its own copy of library data into memory

### Dynamic Relocation
When library code is not position independent:
- Code and data can be loaded at arbitrary addresses
- The dynamic linker (`ld.so`) patches addresses at runtime
- Calculates positions of functions and variables and updates references

### Position Independent Code Solution
The goal is to write code that works regardless of where it's loaded in memory.

**Key Technique:**
```assembly
f( ) { 
    call next;     // Get current instruction address
    next: pop R1   // R1 now contains current address
    add R1, #(g - next), R2  // Calculate absolute address of function g
    call ind R2    // Indirect call to g
    add R1, #(y - next), R2  // Calculate absolute address of variable y
    load ind R2, R3
}
```

### Global Offset Table (GOT) and Procedure Linkage Table (PLT)
- **GOT**: Contains addresses of global variables and functions
- **PLT**: Contains stubs for calling external functions
- Each process has:
  - Different copies of data
  - Shared code
  - Shared PLT
  - Different copy of GOT

### Lazy Binding
- Optimization technique that delays address resolution
- Function addresses are determined only when first called
- Significantly reduces program startup time
- Reduces overall dynamic linking overhead

## File Systems

### Files
- **Definition**: A sequence of bytes with no OS interpretation
- **Components**:
  - **Data**: The actual file content
  - **Metadata**: Information about the file
    - Size
    - Permissions/Owner
    - Timestamps
    - Location of data on disk
    - Filename (in UNIX, filename is metadata, directory name is data)

### Directories
- Collection of files for easy management
- Hierarchical structure allowing subdirectories
- Enables organized file system navigation

### Inodes
- **Definition**: Structure that stores file metadata
- Each inode has a unique inode number within a file system
- **Note**: Filename is NOT stored in the inode

### File Permissions
File permissions are based on:
- **Owner**: User ID (uid) of the file owner
- **Group**: Group to which the user belongs

**Key Commands**:
- `chown`: Changes file owner (requires superuser privileges)
- `chgrp`: Changes group (user must belong to the target group)

## Key Concepts Summary
1. **Position Independence**: Enables code sharing between processes
2. **Dynamic Linking**: Reduces memory usage through shared libraries
3. **File Abstraction**: OS treats files as byte sequences
4. **Metadata Management**: Inodes store file information separately from data
5. **Permission System**: Unix-style owner/group permission model
