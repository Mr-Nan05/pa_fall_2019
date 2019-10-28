#include "cpu/instr.h"


make_instr_func(lgdt){
#ifdef IA32_SEG
    int len = 1;

    opr_src.data_size = data_size;
    len += modrm_rm(eip + 1, &opr_src);

    uint32_t addr = opr_src.addr;

    OPERAND limit,base;
    limit.data_size = 16;   base.data_size = 32;
    limit.type = OPR_MEM;   base.type = OPR_MEM;
    limit.sreg = SREG_DS;   base.sreg = SREG_DS;
    limit.addr = addr;      base.addr = addr + 2;
    operand_read(&limit);   operand_read(&base);
    
    cpu.gdtr.limit = limit.val;
    if(data_size == 16)
        cpu.gdtr.base = base.val & 0x00ffffff;
    else 
        cpu.gdtr.base = base.val;

    print_asm_1("lgdt","",2,&opr_src);
    return len;
#else
    printf("please implement lgdt\n");assert(0);
#endif
}


