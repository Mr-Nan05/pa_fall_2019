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
    uint32_t esp = cpu.esp;
    uint32_t esp_decrease = (data_size/8)*8;
    cpu.esp -= esp_decrease ;
    
    if(data_size == 16){
        OPERAND r0,r1,r2,r3,r4,r5,r6,r7;
        r0.type=r1.type=r2.type=r3.type=r4.type=r5.type=r6.type=r7.type=OPR_MEM;
        r0.sreg=r1.sreg=r2.sreg=r3.sreg=r4.sreg=r5.sreg=r6.sreg=r7.sreg=SREG_SS;
        r0.data_size=r1.data_size=r2.data_size=r3.data_size=r4.data_size=r5.data_size=r6.data_size=r7.data_size=16;
        r0.addr = esp - 2;
        r1.addr = esp - 4;
        r2.addr = esp - 6;
        r3.addr = esp - 8;
        r4.addr = esp - 10;
        r5.addr = esp - 12;
        r6.addr = esp - 14;
        r7.addr = esp - 16;
        r0.val = cpu.eax & 0xffff;
        r1.val = cpu.ecx & 0xffff;
        r2.val = cpu.edx & 0xffff;
        r3.val = cpu.ebx & 0xffff;
        r4.val = esp & 0xffff;
        r5.val = cpu.ebp & 0xffff;
        r6.val = cpu.esi & 0xffff;
        r7.val = cpu.edi & 0xffff;
        operand_write(&r0);
        operand_write(&r1);
        operand_write(&r2);
        operand_write(&r3);
        operand_write(&r4);
        operand_write(&r5);
        operand_write(&r6);
        operand_write(&r7);
    }
    else if (data_size == 32){
        OPERAND r0,r1,r2,r3,r4,r5,r6,r7;
        r0.type=r1.type=r2.type=r3.type=r4.type=r5.type=r6.type=r7.type=OPR_MEM;
        r0.sreg=r1.sreg=r2.sreg=r3.sreg=r4.sreg=r5.sreg=r6.sreg=r7.sreg=SREG_SS;
        r0.data_size=r1.data_size=r2.data_size=r3.data_size=r4.data_size=r5.data_size=r6.data_size=r7.data_size = 32;
        r0.addr = esp - 4;
        r1.addr = esp - 8;
        r2.addr = esp - 12;
        r3.addr = esp - 16;
        r4.addr = esp - 20;
        r5.addr = esp - 24;
        r6.addr = esp - 28;
        r7.addr = esp - 32;
        r0.val = cpu.eax ;
        r1.val = cpu.ecx ;
        r2.val = cpu.edx ;
        r3.val = cpu.ebx ;
        r4.val = esp ;
        r5.val = cpu.ebp ;
        r6.val = cpu.esi ;
        r7.val = cpu.edi ;
        operand_write(&r0);
        operand_write(&r1);
        operand_write(&r2);
        operand_write(&r3);
        operand_write(&r4);
        operand_write(&r5);
        operand_write(&r6);
        operand_write(&r7);
    }
    print_asm_0("pusha","",1);
    return len;
#else
     printf("please implement pusha\n"); assert(0);
#endif
}