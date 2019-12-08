#include "cpu/instr.h"

OPERAND for_limit(uint32_t addr)
{   
    OPERAND limit;
    limit.data_size = 16;  
    limit.type = OPR_MEM; 
    limit.sreg = SREG_DS; 
    limit.addr = addr;  
    return limit;
}

OPERAND for_base(uint32_t addr)
{
    OPERAND base;
       base.data_size = 32;
      base.type = OPR_MEM;
      base.sreg = SREG_DS;
        base.addr = addr + 2;
        return base;
}

void lgdt_choose(OPERAND limit, OPERAND base)
{
    cpu.gdtr.limit = limit.val;
    if(data_size == 16)
        cpu.gdtr.base = base.val & 0x00ffffff;
    else 
        cpu.gdtr.base = base.val;
}

make_instr_func(lgdt){
#ifdef IA32_SEG
    opr_src.data_size = data_size;
    int len = 1 + modrm_rm(eip + 1, &opr_src);

    uint32_t addr = opr_src.addr;
    OPERAND limit = for_limit(addr);
    OPERAND base = for_base(addr);
    //gdtr_change(base,limit, addr);
      //operand_lgdt(limit,base, addr);
    operand_read(&limit);   operand_read(&base);
    lgdt_choose(limit, base);
    print_asm_1("lgdt","",2,&opr_src);
    return len;
#else
    printf("please implement lgdt\n");assert(0);
#endif
}


