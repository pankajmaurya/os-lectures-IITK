# Operating Systems (CS330) - Lecture 30

## Overview
This lecture covers the program loading process, object files, linking, and library management in operating systems. The content focuses on how executable files are structured and loaded into memory to create running processes.

## Key Topics Covered

### 1. Program Header Table
- **Purpose**: Array of entries describing file areas to be loaded into memory for creating executable process images
- **Location**: Size and number of entries specified in the ELF header
- **Contents**: Each entry contains:
  - Type
  - File offset
  - Virtual address
  - File size
  - Memory image size
  - Alignment information

### 2. ELF File Structure

#### Sections
Various types of sections are described by entries in the section header table, which can hold different types of program data.

#### Section Header Table
- Contains a section header for every section in the file
- Provides detailed information about each corresponding section

### 3. Program Loading Process

#### Kernel Loading Procedure
The kernel follows a specific process to load files into memory for execution.

#### Stack Management Challenge
- **Problem**: Determining how many stack pages to allocate initially
- **Solution**: Dynamic stack growth
  - Process starts with 1-2 stack pages
  - Stack grows on demand when page faults occur
  - Page fault handler recognizes stack space needs and allocates additional pages
  - Inaccessible hole between data and stack areas allows bidirectional growth

### 4. Object Files

#### Creation and Purpose
- Generated by assembler after assembling assembly programs
- Contains machine code and data for source files
- Each compiled source file produces one object file
- Later linked with libraries to create executable files

#### Key Characteristics
- Symbols (functions, global variables) cannot be assigned addresses until linking
- Similar format to executables but with additional linking information
- Contains symbol table (imported/exported symbols)
- Includes relocation table for address patching

### 5. Linking Process

#### Linker Operations
1. **Input Processing**: Takes set of object files as input
2. **Size Determination**: Scans files to determine code and data section sizes
3. **Section Consolidation**: Combines sections from various files
4. **Address Assignment**: Assigns addresses to all symbols using:
   - Starting addresses of code/data from each object file
   - Symbol table offsets
5. **Relocation**: Patches absolute references with correct values

#### Relocation Example
```c
// file1.c
...
g(); // call to function 'g'
...

// file2.c
...
void g(){
    ...
}
...
```

In this example:
- `file1.c` calls function `g` defined in `file2.c`
- Object file `file1.o` contains relocation entry specifying:
  - Location for relocation
  - Type of relocation
  - Symbol name (`g`)
- Linker performs relocation after assigning addresses

### 6. Library Management

#### Static Libraries
- **Windows**: `.lib` files
- **Unix**: `.a` files
- Essentially collections of object files in specific format
- Linker only includes necessary object files from specified libraries

#### Dynamic Libraries
- **Advantages**:
  - Saves disk space and memory
  - No relinking required when library changes
- **Complexity**: More complex linking process (covered in subsequent lectures)

## Process Flow Summary

1. **Source Code** → **Assembly** → **Object Files**
2. **Object Files** + **Libraries** → **Linking** → **Executable**
3. **Executable** → **Loading** → **Running Process**

## Important Concepts

- **Symbol Resolution**: Process of matching symbol references with definitions
- **Relocation**: Updating addresses in code after final memory layout is determined
- **Dynamic Stack Growth**: Memory management technique for efficient stack allocation
- **Section-based File Organization**: Structured approach to organizing executable content

---

*This summary is based on CS330 Operating Systems lecture materials from IIT Kanpur.*
