#include "cpu/instr.h"

make_instr_func(leave){
   
    int len = 1;

    cpu.esp = cpu.ebp;
    uint32_t esp_inc = data_size/8;
    uint32_t esp = cpu.esp;

    OPERAND rel;
    rel.type = OPR_MEM;
    rel.sreg = SREG_SS;
    rel.data_size = data_size;
    rel.addr = esp;
    operand_read(&rel);

    cpu.ebp = rel.val;
    cpu.esp += esp_inc;
   
    return len;
}