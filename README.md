# Software CPU Emulator - Recursive Function Execution & CPU Architecture

A complete software-based 16-bit CPU implementation in C, featuring a custom instruction set architecture (ISA), assembler, emulator, and **recursive function execution demo** (Factorial & Multiply).

---

## Demo Video
(Insert your video link here)

---

# Team Members & Contributions

- **Vinuta Patil** – CPU Architecture & ISA Design  
- **Abhinav Sriharsha Anumanchi** – CPU Core & ALU Implementation  
- **Vineela Mukkamala** – Memory Management, Control Flow & Video  
- **Sahithi Chikkela** – Recursive Programs, Testing, Documentation

---

# Architecture Overview

## CPU Schematic

```
┌─────────────────────────────────────────────────────────────┐
│                        CPU CORE                             │
│                                                             │
│  ┌──────────────┐         ┌──────────────┐                  │
│  │   Registers  │         │      ALU     │                  │
│  │              │         │              │                  │
│  │  PC  SP      │◄────────┤  Add  Sub    │                  │
│  │  A   B       │         │  Mul  Div    │                  │
│  │  C   D       │────────►│  And  Or     │                  │
│  │  FLAGS       │         │  Xor  Shift  │                  │
│  └──────────────┘         └──────────────┘                  │
│         │                         │                         │
│         ▼                         ▼                         │
│  ┌──────────────────────────────────────┐                   │
│  │         Control Unit                 │                   │
│  │  ┌────────────┐    ┌──────────────┐  │                   │
│  │  │   Fetch    │───►│    Decode    │  │                   │
│  │  └────────────┘    └──────────────┘  │                   │
│  │         │                  │         │                   │
│  │         ▼                  ▼         │                   │
│  │  ┌────────────────────────────────┐  │                   │
│  │  │         Execute                │  │                   │
│  │  └────────────────────────────────┘  │                   │
│  └──────────────────────────────────────┘                   │
│                      │                                      │
└──────────────────────┼──────────────────────────────────────┘
                       │
                       ▼
        ┌──────────────────────────────┐
        │         System Bus           │
        └──────────────────────────────┘
                       │
        ┌──────────────┴──────────────┐
        │                             │
        ▼                             ▼
┌───────────────┐           ┌─────────────────┐
│    Memory     │           │  Memory-Mapped  │
│    (64KB)     │           │      I/O        │
│               │           │                 │
│  0x0000-0xFEFF│           │  0xFF00: Input  │
│               │           │  0xFF01: Output │
│               │           │  0xFF03: Timer  │
└───────────────┘           └─────────────────┘
```

---

# Instruction Set Architecture (ISA)

## Instruction Format

```
┌─────────────┬──────────────┬─────────────────────┐
│   Opcode    │     Mode     │      Operand        │
│   (6 bits)  │   (2 bits)   │   (0–16 bits)       │
└─────────────┴──────────────┴─────────────────────┘
```

## Addressing Modes

| Mode | Code | Meaning |
|------|------|---------|
| Immediate | 00 | Literal value |
| Direct | 01 | Direct memory address |
| Register | 10 | Register operand |
| Indirect | 11 | Value at address stored in register |

## Registers
- **PC** – Program Counter  
- **SP** – Stack Pointer  
- **A, B, C, D** – General-purpose registers  
- **FLAGS** – Z, C, N, O, H  

---

# Memory Map

```
0x0000 - 0xFEFF : General Memory  
0xFF00 : Keyboard Input  
0xFF01 : Console Output  
0xFF03 : Hardware Timer  
```

---

# Recursion Implementation on CPU Emulator

This project demonstrates recursion implemented in **assembly**, executed on the software CPU using **CALL**, **RET**, and **stack-based parameter passing**.

## Recursive Programs Included
### 1. factorial_recursive.asm  
Computes `n!` using:  
```
fact(n):
    if n <= 1: return 1
    else: return n * fact(n-1)
```

### 2. multiply_recursive.asm  
Computes multiplication using repeated addition:  
```
multiply(a, b):
    if b == 0: return 0
    else: return a + multiply(a, b-1)
```

---

# CALL / RET Mechanism

### CALL performs:
- Push return address  
- Push saved registers  
- Jump to function start  

### RET performs:
- Pop saved registers  
- Pop return address  
- Continue execution  

---

# Running the Recursion Programs

## Step 1 — Build Project
```
make clean
make
```

## Step 2 — Assemble & Run Recursive FACTORIAL
```
./cpu_emulator assemble factorial_recursive.asm factorial.bin
./cpu_emulator run factorial.bin
./cpu_emulator demo factorial_recursive
```

## Step 3 — Assemble & Run Recursive MULTIPLY
```
./cpu_emulator assemble multiply_recursive.asm multiply.bin
./cpu_emulator run multiply.bin
./cpu_emulator demo multiply_recursive
```

---

# C Program Versions (for comparison)

```
gcc factorial.c -o factorial
./factorial

gcc multiply.c -o multiply
./multiply
```

---

# Project Structure

```
├── cpu.c
├── cpu.h
├── assembler.c
├── assembler.h
├── factorial_recursive.asm
├── multiply_recursive.asm
├── factorial.c
├── multiply.c
├── Makefile
├── video.mp4
└── README.md
```

---

# Educational Value
- Demonstrates how recursion works at low level  
- Shows stack frame construction & destruction  
- Visualizes CALL/RET behavior  
- Bridges high-level C recursion with assembly  

