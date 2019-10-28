#include "cpu/instr.h"

make_instr_func(ret_near){

    uint32_t esp = cpu.esp;
    uint32_t esp_inc = data_size/8;
    
    OPERAND rel;
    rel.type = OPR_MEM;
    rel.sreg = SREG_SS;
    rel.data_size = data_size;
    rel.addr = esp;
    operand_read(&rel);

    cpu.eip = rel.val;
    cpu.esp += esp_inc;

    return 0;
}

make_instr_func(ret_near_imm16){
    uint32_t esp = cpu.esp;
    uint32_t esp_inc = data_size/8;

    OPERAND imm;
    imm.type = OPR_IMM;
    imm.sreg = SREG_CS;
    imm.data_size = 16;
    imm.addr = eip + 1;
    operand_read(&imm);
    uint32_t esp_imm=sign_ext(imm.val,16);

    OPERAND rel;
    rel.type = OPR_MEM;
    rel.sreg = SREG_SS;
    rel.data_size = data_size;
    rel.addr = esp;
    operand_read(&rel);

    cpu.eip = rel.val;
    cpu.esp += esp_imm+esp_inc;

    return 0;
}

