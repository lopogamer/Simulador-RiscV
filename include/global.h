#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>

#define UByte uint8_t
#define Byte int8_t
#define Word int32_t
#define UWord uint32_t

#define MEM_SIZE 16384       // Tamanho da memória
#define NUM_REGISTERS 32     // Número de registradores

extern UWord Reg[NUM_REGISTERS];  // Registradores
extern Byte Mem[MEM_SIZE];        // Memória principal
extern int Out;                   // Tipo de saída (ECALL ou fim de memória)
extern UWord pc;                  // Program Counter
extern UWord ri;                  // Registrador de instrução
extern UWord sp;                  // Stack Pointer
extern UWord gp;                  // General Purpose Register
typedef struct {
    Word ins_code;     // Código da instrução
    UWord ins_format;   // Formato da instrução
    UWord rs1;          // Registrador 1
    UWord rs2;          // Registrador 2
    UWord rd;           // Registrador de destino
    UWord shamt;        // Quantidade de shifts
    Word imm_i;         // Imediato tipo I
    Word imm_s;         // Imediato tipo S
    Word imm_j;         // Imediato tipo J
    Word imm_u;         // Imediato tipo U
    Word imm_b;         // Imediato tipo B
} instruction_context_st;
extern instruction_context_st ic; // Contexto da instrução
#endif
