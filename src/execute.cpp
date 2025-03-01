#include "global.h"
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;
#include <map>
#include <string>
using namespace std;
void zera_r0(){
    Reg[0] = 0;
}


void ADD(UWord rd, UWord rs1, UWord rs2) {  //0
    Reg[rd] = Reg[rs1] + Reg[rs2];  
}
void ADDI(UWord rd, UWord rs1, Word imm) { //1
    Reg[rd] = (UWord)((Word)Reg[rs1] + imm);
}

void AND(UWord rd, UWord rs1, UWord rs2){ //2
    Reg[rd] = Reg[rs1] & Reg[rs2];
}

void ANDI(UWord rd, UWord rs1, Word imm){  //3
    Reg[rd] = Reg[rs1] & imm;
}

void AUIPC(UWord rd, Word imm){
    Reg[rd] = imm + pc;
}
void BEQ(UWord rs1, UWord rs2, Word label){ //5
    if((Word)Reg[rs1] == (Word)Reg[rs2]){
        pc += (label - 4);
    }
}

void BNE(UWord rs1, UWord rs2, Word offset){ //6
    if (Reg[rs1] != Reg[rs2]){
        pc += offset - 4;
    }
}

void BGE(UWord rs1, UWord rs2, Word label){ //
    if((Word)Reg[rs1] >= (Word)Reg[rs2]){
        pc += label - 4;
    }
} 
void BGEU(UWord rs1, UWord rs2, Word label){ //8
    UWord temp = (UWord)Reg[rs2];
    if(Reg[rs1] >= temp){
        pc += label - 4;
    }    
} 

void BLT(UWord rs1, UWord rs2, Word label){ //9
    if((Word)Reg[rs1] < (Word)Reg[rs2]){
        pc += label - 4;
    }
}

void BLTU(UWord rs1, UWord rs2, Word label){ //10
    UWord temp = (UWord)Reg[rs2];
    if((UWord)Reg[rs1] < temp){
        pc += (label - 4);
    }
}

void JAL(UWord rd, Word label){ //11
    Reg[rd] = pc;
    pc += (label - 4);
}

void JALR(UWord rd, UWord rs1, Word label){ //12 
    Word target = (Reg[rs1] + label) & ~1; 
    Reg[rd] = pc -4;
    pc = target;
}

void LB(UWord rd, UWord rs1, Word offset){ //13
    Byte temp = Mem[Reg[rs1] + offset];
    Reg[rd] = (Word)temp;
}

void OR(UWord rd, UWord rs1, UWord rs2){ //14
    Reg[rd] = Reg[rs1] | Reg[rs2];
}

void LBU(UWord rd, UWord rs1, Word offset) { //15
    UByte temp = (UByte)Mem[Reg[rs1] + (offset)];  
    Reg[rd] = (Word)temp;                
}


void LW(UWord rd, UWord rs1, Word offset){ //16
    Word addr = Reg[rs1] + offset;
    UByte byte0 = Mem[addr];
    UByte byte1 = Mem[addr + 1];
    UByte byte2 = Mem[addr + 2];
    UByte byte3 = Mem[addr + 3];
    Reg[rd] = byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24);
}
void LUI(UWord rd, Word imm){ //17
    Reg[rd] = imm;
}
void SLT(UWord rd, UWord rs1, UWord rs2){ // 18
    if((Word)Reg[rs1] < (Word)Reg[rs2]){
        Reg[rd] = 0x00000001;
    }else{
        Reg[rd] = 0x00000000;
    }
}
void SLTU(UWord rd, UWord rs1, UWord rs2){ //19
    UWord temp = (UWord)Reg[rs2];
    if(Reg[rs1] < temp){
        Reg[rd] = 0x00000001;
    }else{
        Reg[rd] = 0x00000000;
    }
}
void ORI(UWord rd, UWord rs1, Word imm){ // 20
    Reg[rd] = Reg[rs1] | imm;
}

void SB(UWord rs1, UWord rs2, Word offset){ //21 
    Byte temp = Reg[rs2];
    Mem[Reg[rs1] + offset] = temp & 0xFF;
}

void SLLI(UWord rd, UWord rs1, Word imm){  //22
    Reg[rd] = (Word)Reg[rs1] << imm;
}

void SRLI(UWord rd, UWord rs1, Word imm){  //23
    Reg[rd] = Reg[rs1] >> imm;
}
void SRAI(UWord rd, UWord rs1, Word imm){  // 24
    Reg[rd] = ((signed)Reg[rs1]) >> imm;
}

void SUB(UWord rd, UWord rs1, UWord rs2){ // 25
    Reg[rd] = Reg[rs1] - Reg[rs2];
}

void SW(UWord rs2, UWord rs1, Word offset){ //26
    Word value = Reg[rs2];
    Mem[Reg[rs1] + offset] = value & 0xFF;              
    Mem[Reg[rs1] + offset + 1] = (value >> 8) & 0xFF;   
    Mem[Reg[rs1] + offset + 2] = (value >> 16) & 0xFF;  
    Mem[Reg[rs1] + offset + 3] = (value >> 24) & 0xFF; 
}
void XOR(UWord rd, UWord rs1, UWord rs2){ //27
    Reg[rd] = Reg[rs1] ^ Reg[rs2];
}


void print() {
    Word addr = Reg[10];  // Achar o endereço armazenado em Reg[10]
    int i = 0;
    while (Mem[addr + i] != 0) {  // Le cada byte da memoria e imprime o caractere correspondente
        char caracter = static_cast<char>(Mem[addr + i]);  // Converte o byte para um caractere
        cout << caracter;  // Imprime o caractere
        i++;
    }
    return;
}
void ecall() {
    if (Reg[17] == 10) {
        Out = 2;
    } else if (Reg[17] == 1) {
        cout << (Word)Reg[10]; // Imprime o valor do registrador a0
    }else if (Reg[17] == 4){
        print(); // Imprime a string começando no endereço armazenado em a0
    }else{
        cout << "Erro: Chamada de sistema não implementada" << endl;
    }
    return;
}

void execute() {
    UWord instrucao = ic.ins_code;
    zera_r0();
    try {
        switch (instrucao) {
            case 0: 
                //cout << "ADD" << endl;
                ADD(ic.rd, ic.rs1, ic.rs2);
                break;
            case 1: 
                //cout << "ADDI" << endl;
                ADDI(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 2: 
                //cout << "AND" << endl;
                AND(ic.rd, ic.rs1, ic.rs2);
                break;
            case 3: 
                //cout << "ANDI" << endl;
                ANDI(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 4: 
                //cout << "AUIPC" << endl;
                AUIPC(ic.rd, ic.imm_u);
                break;
            case 5: 
                // cout << "BEQ" << endl;
                BEQ(ic.rs1, ic.rs2, ic.imm_b);
                break;
            case 6: 
                //cout << "BNE" << endl;
                BNE(ic.rs1, ic.rs2, ic.imm_b);
                break;
            case 7: 
                //cout << "BGE" << endl;
                BGE(ic.rs1, ic.rs2, ic.imm_b);
                break;
            case 8: 
                //cout << "BGEU" << endl;
                BGEU(ic.rs1, ic.rs2, ic.imm_b);
                break;
            case 9: 
                //cout << "BLT" << endl;
                BLT(ic.rs1, ic.rs2, ic.imm_b);
                break;
            case 10: 
                //cout << "BLTU" << endl;
                BLTU(ic.rs1, ic.rs2, ic.imm_b);
                break;
            case 11: 
                //cout << "JAL" << endl;
                JAL(ic.rd, ic.imm_j);
                break;
            case 12: 
                //cout << "JALR" << endl;
                JALR(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 13: 
                // cout << "LB" << endl;
                LB(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 14: 
                //cout << "OR" << endl;
                OR(ic.rd, ic.rs1, ic.rs2);
                break;
            case 15: 
                //cout << "LBU" << endl;
                LBU(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 16: 
                LW(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 17: 
                //cout << "LUI" << endl;
                LUI(ic.rd, ic.imm_u);
                break;
            case 18: 
                //cout << "SLT" << endl;
                SLT(ic.rd, ic.rs1, ic.rs2);
                break;
            case 19: 
                //cout << "SLTU" << endl;
                SLTU(ic.rd, ic.rs1, ic.rs2);
                break;
            case 20: 
                //cout << "ORI" << endl;
                ORI(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 21: 
                //cout << "SB" << endl;
                SB(ic.rs1, ic.rs2, ic.imm_s);
                break;
            case 22: 
                //cout << "SLLI" << endl;
                SLLI(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 23: 
                //cout << "SRLI" << endl;
                SRLI(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 24: 
                //cout << "SRAI" << endl;
                SRAI(ic.rd, ic.rs1, ic.imm_i);
                break;
            case 25: 
                //cout << "SUB" << endl;
                SUB(ic.rd, ic.rs1, ic.rs2);
                break;
            case 26: 
                //cout << "SW" << endl;
                SW(ic.rs2, ic.rs1, ic.imm_s);
                break;
            case 27: 
                //cout << "XOR" << endl;
                XOR(ic.rd, ic.rs1, ic.rs2);
                break;
            case 28:
                //cout << "ECALL" << endl;
                ecall();
                break;
            default:
                break;
        }
    } catch (const exception& e) {
        cerr << "Erro ao executar a instrucao: " << instrucao << ' ' << e.what() << endl;
    }
}
