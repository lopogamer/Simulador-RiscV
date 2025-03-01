#include <stdint.h>
#include "global.h"
#include <iostream>
using namespace std;


Word get_instr_code(uint32_t opcode, UWord funct3, UWord funct7) {
    if (opcode == 0b0110011) { // Tipo R
        if (funct3 == 0x0 && funct7 == 0x00) return 0; // ADD
        else if (funct3 == 0x7 && funct7 == 0x00) return 2; // AND
        else if (funct3 == 0x6 && funct7 == 0x00) return 14; // OR
        else if (funct3 == 0x2 && funct7 == 0x00) return 18; // SLT
        else if (funct3 == 0x3 && funct7 == 0x00) return 19; // SLTU
        else if (funct3 == 0x0 && funct7 == 0x20) return 25; // SUB
        else if (funct3 == 0x4 && funct7 == 0x00) return 27; // XOR
    }
    else if (opcode == 0b0010011) { // Tipo I
        if (funct3 == 0x0) return 1; // ADDI
        else if (funct3 == 0x7) return 3; // ANDI
        else if (funct3 == 0x6) return 20; // ORI
        else if (funct3 == 0x1) return 22; // SLLI
        else if (funct3 == 0x5 && funct7 == 0x00) return 23; // SRLI
        else if (funct3 == 0x5 && funct7 == 0x20) return 24; // SRAI
    }
    else if (opcode == 0b0110111) { // LUI
        return 17;
    }
    else if (opcode == 0b0010111) { // AUIPC
        return 4;
    }
    else if (opcode == 0b1100011) { // Tipo B
        if (funct3 == 0x0) return 5; // BEQ
        else if (funct3 == 0x1) return 6; // BNE
        else if (funct3 == 0x5) return 7; // BGE
        else if (funct3 == 0x7) return 8; // BGEU
        else if (funct3 == 0x4) return 9; // BLT
        else if (funct3 == 0x6) return 10; // BLTU
    }
    else if (opcode == 0b1101111) { // JAL
        return 11;
    }
    else if (opcode == 0b1100111) { // JALR
        return 12;
    }
    else if (opcode == 0b0000011) { // Tipo I (Load)
        if (funct3 == 0x0) return 13; // LB
        else if (funct3 == 0x4) return 15; // LBU
        else if (funct3 == 0x2) return 16; // LW
    }
    else if (opcode == 0b0100011) { // Tipo S
        if (funct3 == 0x0) return 21; // SB
        else if (funct3 == 0x2) return 26; // SW
    }
    else if (opcode == 0b1110011 && funct3 == 0x0) { // ECALL
        return 28;
    }
    return -1; // Código de erro se a instrução não for encontrada
}

Word get_i_format(UWord opcode) {
    switch (opcode) {
        case 0x33: // R-type instructions (e.g., ADD, SUB, etc.)
            return 1; // R_FORMAT
        case 0x13: // I-type instructions (e.g., ADDI, ANDI, etc.)
            return 2; // I_FORMAT
        case 0x03: // I-type load instructions (e.g., LB, LH, LW)
            return 2; // I_FORMAT
        case 0x23: // S-type instructions (e.g., SB, SH, SW)
            return 3; // S_FORMAT
        case 0x63: // B-type instructions (e.g., BEQ, BNE, etc.)
            return 4; // B_FORMAT
        case 0x37: // U-type instructions (e.g., LUI)
            return 5; // U_FORMAT
        case 0x17: // U-type instructions (e.g., AUIPC)
            return 5; // U_FORMAT
        case 0x6F: // J-type instructions (e.g., JAL)
            return 6; // J_FORMAT
        default:
            return 0; // UNKNOWN_FORMAT
    }
}
Word get_imm(UWord ri, UWord instr_type) {
    Word imm = 0;
    switch (instr_type) {
        case 2: {
            imm = (ri & 0xFFF00000) >> 20;
            if (imm & 0x00000800) {
                imm |= 0xFFFFF000;
            }
            break;
        }
        case 3: {
            Word imm7 = (ri & 0xFE000000) >> 25;
            Word imm5 = (ri & 0x00000F80) >> 7;
            imm = (imm7 << 5) | imm5;
            if (imm & 0x00001000) {
                imm |= 0xFFFFE000;
            }
            break;
        }
        case 4: {
            int bit_12 = (ri >> 31) & 1;
            int bit_11 = (ri >> 7) & 1;
            Word imm6 = (ri & 0x7E000000) >> 25;
            Word imm4 = (ri & 0x00000F00) >> 8;
            imm = (bit_12 << 12) | (bit_11 << 11) | (imm6 << 5) | (imm4 << 1);
            if (bit_12) {
                imm |= 0xFFFFF000;
            }
            break;
        }
        case 5: {
            imm = ri & 0xFFFFF000;
            break;
        }
        case 6: {
            int bit_20 = (ri >> 31) & 1;
            int bit_11 = (ri >> 20) & 1;
            Word imm9 = (ri & 0x7FE00000) >> 21;
            Word imm8 = (ri & 0x000FF000) >> 12;
            imm = (bit_20 << 20) | (imm8 << 12) | (bit_11 << 11) | (imm9 << 1);
            if (bit_20) {
                imm |= 0xFFF00000;
            }
            break;
        }
    }
    return imm;
}

void decode (){
    UWord opcode, rs2, rs1, rd, shamt, funct3, funct7;
    opcode	= ri & 0x7F;

    rs2		= (ri >> 20) & 0x1F;
    rs1		= (ri >> 15) & 0x1F;
    rd		= (ri >> 7)  & 0x1F;
    shamt	= (ri >> 20) & 0x1F;
    funct3	= (ri >> 12) & 0x7;
    funct7  = (ri >> 25);				
    ic.ins_code = get_instr_code(opcode, funct3, funct7);
    ic.ins_format = get_i_format(opcode);
    ic.rs1 = rs1;
    ic.rs2 = rs2;
    ic.rd = rd;
    ic.shamt = shamt;
    ic.imm_i = get_imm(ri, ic.ins_format);
    ic.imm_s = get_imm(ri, ic.ins_format);
    ic.imm_j = get_imm(ri, ic.ins_format);
    ic.imm_u = get_imm(ri, ic.ins_format);
    ic.imm_b = get_imm(ri, ic.ins_format);
}