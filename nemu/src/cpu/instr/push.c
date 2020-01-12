#include "cpu/instr.h"

static void instr_execute_1op(){
   
    operand_read(&opr_src);
    uint32_t val = opr_src.val;

    uint32_t esp_de = data_size/8;
    cpu.esp-= esp_de;
    uint32_t esp = cpu.esp;

    OPERAND rel;
    rel.type = OPR_MEM;
    rel.sreg = SREG_SS;
    rel.addr = esp;
    rel.data_size = data_size;
    rel.val = val;
    operand_write(&rel);
}

make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,i,v)
make_instr_impl_1op(push,i,b)

make_instr_func(pusha){
#ifdef  IA32_INTR
    int len = 1;
    
    print_asm_0("pusha","",1);
    return len;
#else
     printf("please implement pusha\n"); assert(0);
#endif
}