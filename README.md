# Assembly Addressing Modes Demonstration

This repository demonstrates **all 9 common assembly addressing modes** using an example program written in **C** and its corresponding **assembly implementation**.

> Repo language stats show 100% C, but the project includes/assumes an accompanying assembly source file (often stored as `.s` / `.asm`) that implements the same behavior as the C program while showcasing the addressing modes.

---

## Goal

The goal is to show how a single (small) C program can be translated into assembly in a way that deliberately uses the following addressing modes:

1. **Immediate addressing**
2. **Register addressing**
3. **Direct (absolute) memory addressing**
4. **Register indirect addressing**
5. **Indexed addressing**
6. **Base + displacement (base-relative) addressing**
7. **Scaled indexed addressing**
8. **PC-relative addressing**
9. **Implied (implicit) addressing**

The exact syntax and instruction set can vary (x86, ARM, RISC-V, etc.), but the concepts are the same. The assembly file in this repo is written to include explicit examples of each mode.

---

## How the C program maps to the addressing modes

The C program is structured around:

- Using constants
- Using local variables (stack)
- Using global/static variables
- Using pointers
- Accessing arrays
- Calling functions
- Using control flow (loops/branches)

These elements naturally force the compiler (or a hand-written assembly implementation) to access data in different ways. Below is how each addressing mode is represented in the assembly.

---

## 1) Immediate Addressing

**Meaning:** The operand value is encoded directly inside the instruction.

**Where it appears:**

- Assigning constants
- Initializing counters
- Adding/subtracting a fixed constant

**Typical assembly example:**

- `mov r0, #5` (ARM)
- `li t0, 5` (RISC-V)
- `mov eax, 5` (x86)

In the program, constants like loop bounds, initial values, and constant increments are implemented using immediate operands.

---

## 2) Register Addressing

**Meaning:** The operand is located in a CPU register.

**Where it appears:**

- Arithmetic between variables that have already been loaded
- Temporary values
- Loop counters stored in registers

**Typical assembly example:**

- `add r1, r1, r2`
- `add t0, t0, t1`

After variables are loaded from memory, most arithmetic and comparisons are performed using register-to-register operations.

---

## 3) Direct (Absolute) Memory Addressing

**Meaning:** The instruction references a fixed memory address/label directly.

**Where it appears:**

- Global variables
- Static storage

**Typical assembly example:**

- `ldr r0, =global_var` (ARM pseudo)
- `lw t0, global_var` (RISC-V w/ relocation)
- `mov eax, [global_var]` (x86)

The program includes at least one global/static variable so that the assembly can demonstrate direct references to a symbol in the data section.

---

## 4) Register Indirect Addressing

**Meaning:** A register holds the memory address of the operand (pointer dereference).

**Where it appears:**

- Pointer variables (`int *p`)
- Dereferencing pointers (`*p`)

**Typical assembly example:**

- `ldr r0, [r1]` (ARM)
- `lw t0, 0(t1)` (RISC-V)
- `mov eax, [rbx]` (x86)

Any time the C program uses pointer dereferencing, the assembly uses register-indirect memory access.

---

## 5) Indexed Addressing

**Meaning:** Effective address is computed as base + index.

**Where it appears:**

- Array indexing like `arr[i]`

**Typical assembly example:**

- `ldr r0, [r1, r2]` (ARM)
- `add t2, t0, t1` then `lw t3, 0(t2)` (RISC-V)
- `mov eax, [rbx + rcx]` (x86)

The code includes an array and uses a variable index so the address is computed using an index register.

---

## 6) Base + Displacement (Base-relative) Addressing

**Meaning:** Effective address is base register + constant offset.

**Where it appears:**

- Accessing local variables on the stack
- Struct fields (if used)

**Typical assembly example:**

- `ldr r0, [sp, #8]` (ARM)
- `lw t0, 12(sp)` (RISC-V)
- `mov eax, [rbp-4]` (x86)

The C program uses local variables, which reside at fixed offsets from the stack/frame pointer, demonstrating base+displacement.

---

## 7) Scaled Indexed Addressing

**Meaning:** Effective address is base + (index * scale) + displacement.

**Where it appears:**

- Accessing arrays of 4-byte or 8-byte elements (e.g., `int arr[i]`)

**Typical assembly example (x86):**

- `mov eax, [rbx + rcx*4]`

Many architectures implement scaling implicitly via shifts/adds; others (like x86) encode scaling directly. In the assembly, array indexing is implemented in a way that makes the element-size scaling visible.

---

## 8) PC-relative Addressing

**Meaning:** The effective address is computed relative to the current program counter.

**Where it appears:**

- Branching to labels (loops, if/else)
- Loading addresses of constants/strings (depending on ISA)
- Function calls/jumps

**Typical assembly example:**

- `b loop_start` (ARM)
- `jal ra, function` (RISC-V)
- `jne .L1` (x86)

The program contains control flow (a loop and/or conditional). All jumps/branches to labels are examples of PC-relative addressing.

---

## 9) Implied (Implicit) Addressing

**Meaning:** The operand is implied by the instruction; it is not explicitly stated.

**Where it appears:**

- Stack operations (`push`, `pop`)
- Return instructions (`ret`)
- Some arithmetic instructions that implicitly use special registers/flags

**Typical assembly example:**

- `ret` (uses return address implicitly)
- `push r4` / `pop r4` (stack pointer implied)
- `mul` variants that implicitly use accumulator registers (ISA-dependent)

The assembly uses standard function prologue/epilogue and return instructions, which rely on implied operands.

---

## How to build / run

### Option A: Compile C only

If you only want to compile the C file:

```sh
gcc -o program main.c
./program
```

### Option B: Build with assembly (if provided)

If there is an assembly file (example: `main.s`):

```sh
gcc -c main.s -o main.o
gcc -c main.c -o cmain.o
# Link whichever entry point you intend to use
# Example if assembly is the entry:
gcc -o program main.o
./program
```

> Adjust filenames as needed to match what is present in the repository.

---

## What to look for in the assembly

When reading the assembly file, search for:

- Constants embedded in instructions → **Immediate**
- Operations using only registers → **Register**
- Loads/stores referencing global labels → **Direct**
- Loads/stores like `[reg]` / `0(reg)` → **Register indirect**
- Address expressions like `base + index` → **Indexed**
- Stack accesses like `[fp + const]` → **Base + displacement**
- Array access using `index*4` (or shifts) → **Scaled indexed**
- Branches/jumps/calls to labels → **PC-relative**
- `ret`, `push/pop`, flag-setting ops → **Implied**

---

## Notes

- Different textbooks sometimes group or rename these modes (e.g., “direct” vs “absolute”, “displacement” vs “base-relative”).
- If you are using a specific ISA (x86-64, ARMv7, AArch64, RISC-V), the exact instruction syntax will differ, but each mode is still identifiable.

---

## License

Use this project freely for learning and coursework unless your course rules require attribution.
