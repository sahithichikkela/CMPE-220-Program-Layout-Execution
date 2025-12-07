#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "assembler.h"

void print_usage(const char *prog_name) {
    printf("Usage:\n");
    printf("  %s assemble <input.asm> <output.bin>  - Assemble program\n", prog_name);
    printf("  %s run <program.bin>                  - Run binary program\n", prog_name);
    printf("  %s demo <factorial_recursive|multiply_recursive>  - Run demo program\n", prog_name);
    printf("\n");
}

/* =========================
 *  Recursive factorial demo
 *  Uses external factorial.bin
 * ========================= */
void create_factorial_recursive_demo(CPU *cpu) {
    printf("Creating Factorial Recursive demo program...\n");
    printf("Loading 'factorial.bin' (assembled from factorial_recursive.asm)...\n");

    FILE *f = fopen("factorial.bin", "rb");
    if (!f) {
        fprintf(stderr,
                "Error: Cannot open 'factorial.bin'.\n"
                "Please run:\n"
                "  ./cpu_emulator assemble factorial_recursive.asm factorial.bin\n"
                "first, then rerun this demo.\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (size <= 0) {
        fprintf(stderr, "Error: factorial.bin is empty or invalid.\n");
        fclose(f);
        return;
    }

    uint8_t *program = malloc(size);
    if (!program) {
        fprintf(stderr, "Error: Out of memory while loading factorial.bin\n");
        fclose(f);
        return;
    }

    fread(program, 1, size, f);
    fclose(f);

    cpu_load_program(cpu, program, (uint16_t)size, 0);
    free(program);

    printf("Program loaded. This is the TRUE recursive factorial implementation.\n");
    printf("It uses CALL, RET, PUSH, and POP to implement recursion on the stack.\n\n");
}

/* =========================
 *  Recursive multiply demo
 *  Uses external multiply.bin
 * ========================= */
void create_multiply_recursive_demo(CPU *cpu) {
    printf("Creating Recursive Multiply demo program...\n");
    printf("Loading 'multiply.bin' (assembled from multiply_recursive.asm)...\n");

    FILE *f = fopen("multiply.bin", "rb");
    if (!f) {
        fprintf(stderr,
                "Error: Cannot open 'multiply.bin'.\n"
                "Please run:\n"
                "  ./cpu_emulator assemble multiply_recursive.asm multiply.bin\n"
                "first, then rerun this demo.\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (size <= 0) {
        fprintf(stderr, "Error: multiply.bin is empty or invalid.\n");
        fclose(f);
        return;
    }

    uint8_t *program = malloc(size);
    if (!program) {
        fprintf(stderr, "Error: Out of memory while loading multiply.bin\n");
        fclose(f);
        return;
    }

    fread(program, 1, size, f);
    fclose(f);

    cpu_load_program(cpu, program, (uint16_t)size, 0);
    free(program);

    printf("Program loaded. This is the recursive multiply implementation.\n");
    printf("It computes multiply(3,4) = 12 using CALL, RET, PUSH, and POP on the stack.\n\n");
}

int main(int argc, char *argv[]) {
    printf("=== Software CPU Emulator ===\n\n");
    
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    /* ========== ASSEMBLE MODE ========== */
    if (strcmp(argv[1], "assemble") == 0) {
        if (argc != 4) {
            printf("Usage: %s assemble <input.asm> <output.bin>\n", argv[0]);
            return 1;
        }
        
        if (assemble_file(argv[2], argv[3])) {
            printf("Assembly successful!\n");
            return 0;
        } else {
            printf("Assembly failed!\n");
            return 1;
        }
    }
    /* ========== RUN MODE ========== */
    else if (strcmp(argv[1], "run") == 0) {
        if (argc != 3) {
            printf("Usage: %s run <program.bin>\n", argv[0]);
            return 1;
        }
        
        FILE *f = fopen(argv[2], "rb");
        if (!f) {
            fprintf(stderr, "Error: Cannot open file '%s'\n", argv[2]);
            return 1;
        }
        
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        uint8_t *program = malloc(size);
        if (!program) {
            fprintf(stderr, "Error: Out of memory while loading '%s'\n", argv[2]);
            fclose(f);
            return 1;
        }

        fread(program, 1, size, f);
        fclose(f);
        
        CPU cpu;
        cpu_init(&cpu);
        cpu_load_program(&cpu, program, (uint16_t)size, 0);
        
        printf("Running program '%s' (%ld bytes)...\n\n", argv[2], size);
        cpu_run(&cpu);
        
        printf("\n");
        cpu_dump_registers(&cpu);
        
        free(program);
        return 0;
    }
    /* ========== DEMO MODE ========== */
    else if (strcmp(argv[1], "demo") == 0) {
        if (argc != 3) {
            printf("Usage: %s demo <factorial_recursive|multiply_recursive>\n", argv[0]);
            return 1;
        }
        
        CPU cpu;
        cpu_init(&cpu);
        
        /* ---- factorial_recursive demo ---- */
        if (strcmp(argv[2], "factorial_recursive") == 0) {
            create_factorial_recursive_demo(&cpu);  // loads factorial.bin

            printf("\n--- CPU Running (recursive factorial) ---\n");

            // If load failed (no program), bail out
            if (cpu.memory[0] == 0 && cpu.regs.PC == 0) {
                return 1;
            }

            cpu.running = true;
            int max_cycles = 300;
            int cycle = 0;

            while (cpu.running && !get_flag(&cpu, FLAG_HALT) && cycle < max_cycles) {
                uint16_t pc_before = cpu.regs.PC;
                uint8_t instruction = cpu.memory[pc_before];
                uint8_t opcode = (instruction >> 2) & 0x3F;
                uint8_t mode = instruction & 0x03;

                cpu_step(&cpu);

                uint8_t zn_flags = 0;
                if (get_flag(&cpu, FLAG_ZERO)) zn_flags |= 0x10;
                if (get_flag(&cpu, FLAG_NEGATIVE)) zn_flags |= 0x01;

                printf("[PC=0x%04X] %-7s | A=0x%04X B=0x%04X C=0x%04X D=0x%04X SP=0x%04X ZN=%02X\n",
                       pc_before, get_instruction_name(opcode, mode),
                       cpu.regs.A, cpu.regs.B, cpu.regs.C, cpu.regs.D,
                       cpu.regs.SP, zn_flags);

                cycle++;
            }

            if (cycle >= max_cycles) {
                printf("\n[Safety limit reached after %d cycles]\n", max_cycles);
            }

            printf("\n[CPU HALTED after %d cycles]\n", cycle);
            printf("\n--- CPU Halted ---\n");
            cpu_dump_registers(&cpu);
            printf("\nRecursive factorial calculated!\n");
            printf("factorial(5) result in register A: %d (expected: 120)\n", cpu.regs.A);
            printf("Result in hexadecimal: 0x%04X\n", cpu.regs.A);
            cpu_dump_memory(&cpu, 0x0000, 0x0040);
        }
        /* ---- multiply_recursive demo ---- */
        else if (strcmp(argv[2], "multiply_recursive") == 0) {
            create_multiply_recursive_demo(&cpu);  // loads multiply.bin

            printf("\n--- CPU Running (recursive multiply) ---\n");

            if (cpu.memory[0] == 0 && cpu.regs.PC == 0) {
                return 1;
            }

            cpu.running = true;
            int max_cycles = 300;
            int cycle = 0;

            while (cpu.running && !get_flag(&cpu, FLAG_HALT) && cycle < max_cycles) {
                uint16_t pc_before = cpu.regs.PC;
                uint8_t instruction = cpu.memory[pc_before];
                uint8_t opcode = (instruction >> 2) & 0x3F;
                uint8_t mode = instruction & 0x03;

                cpu_step(&cpu);

                uint8_t zn_flags = 0;
                if (get_flag(&cpu, FLAG_ZERO)) zn_flags |= 0x10;
                if (get_flag(&cpu, FLAG_NEGATIVE)) zn_flags |= 0x01;

                printf("[PC=0x%04X] %-7s | A=0x%04X B=0x%04X C=0x%04X D=0x%04X SP=0x%04X ZN=%02X\n",
                       pc_before, get_instruction_name(opcode, mode),
                       cpu.regs.A, cpu.regs.B, cpu.regs.C, cpu.regs.D,
                       cpu.regs.SP, zn_flags);

                cycle++;
            }

            if (cycle >= max_cycles) {
                printf("\n[Safety limit reached after %d cycles]\n", max_cycles);
            }

            printf("\n[CPU HALTED after %d cycles]\n", cycle);
            printf("\n--- CPU Halted ---\n");
            cpu_dump_registers(&cpu);
            printf("\nRecursive multiply calculated!\n");
            printf("multiply(3,4) result in register A: %d (expected: 12)\n", cpu.regs.A);
            printf("Result in hexadecimal: 0x%04X\n", cpu.regs.A);
            cpu_dump_memory(&cpu, 0x0000, 0x0040);
        }
        else {
            printf("Unknown demo: %s\n", argv[2]);
            printf("Available demos: factorial_recursive, multiply_recursive\n");
            return 1;
        }
        
        return 0;
    }
    else {
        print_usage(argv[0]);
        return 1;
    }
}
