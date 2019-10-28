#include "cpu/instr.h"

static void instr_execute_1op(){
   
    uint8_t  esp_inc = data_size/8;
    uint32_t esp = cpu.esp;

    operand_read(&opr_src);

    OPERAND rel;
    rel.type = OPR_MEM;
    rel.sreg = SREG_SS;
    rel.data_size = data_size;
    rel.addr = esp;
    operand_read(&rel);
    opr_src.val = rel.val;

    operand_write(&opr_src);
    cpu.esp += esp_inc;

}

make_instr_impl_1op(pop,r,v)

make_instr_func(popa){
#ifdef IA32_INTR
    int len = 1;
    uint32_t esp = cpu.esp;
    uint32_t esp_inc = (data_size/8)*8;
    cpu.esp += esp_inc;

    if(data_size == 16){
        OPERAND r0,r1,r2,r3,r4,r5,r6,r7;
        r0.type=r1.type=r2.type=r3.type=r4.type=r5.type=r6.type=r7.type=OPR_MEM;
        r0.sreg=r1.sreg=r2.sreg=r3.sreg=r4.sreg=r5.sreg=r6.sreg=r7.sreg=SREG_SS;
        r0.data_size=r1.data_size=r2.data_size=r3.data_size=r4.data_size=r5.data_size=r6.data_size=r7.data_size=16;
        r0.addr = esp;
        r1.addr = esp + 2;
        r2.addr = esp + 4;
        r3.addr = esp + 6;
        r4.addr = esp + 8;
        r5.addr = esp + 10;
        r6.addr = esp + 12;
        r7.addr = esp + 14;
        operand_read(&r0);
        operand_read(&r1);
        operand_read(&r2);
        operand_read(&r3);
        operand_read(&r4);
        operand_read(&r5);
        operand_read(&r6);
        operand_read(&r7);
        cpu.edi = (cpu.edi & 0xffff0000) + r0.val;
        cpu.esi = (cpu.esi & 0xffff0000) + r1.val;
        cpu.ebp = (cpu.ebp & 0xffff0000) + r2.val;
        cpu.ebx = (cpu.ebx & 0xffff0000) + r4.val;
        cpu.edx = (cpu.edx & 0xffff0000) + r5.val;
        cpu.ecx = (cpu.ecx & 0xffff0000) + r6.val;
        cpu.eax = (cpu.eax & 0xffff0000) + r7.val;
    }
    else if(data_size == 32){
        OPERAND r0,r1,r2,r3,r4,r5,r6,r7;
        r0.type=r1.type=r2.type=r3.type=r4.type=r5.type=r6.type=r7.type=OPR_MEM;
        r0.sreg=r1.sreg=r2.sreg=r3.sreg=r4.sreg=r5.sreg=r6.sreg=r7.sreg=SREG_SS;
        r0.data_size=r1.data_size=r2.data_size=r3.data_size=r4.data_size=r5.data_size=r6.data_size=r7.data_size=32;
        r0.addr = esp;
        r1.addr = esp + 4;
        r2.addr = esp + 8;
        r3.addr = esp + 12;
        r4.addr = esp + 16;
        r5.addr = esp + 20;
        r6.addr = esp + 24;
        r7.addr = esp + 28;
        operand_read(&r0);
        operand_read(&r1);
        operand_read(&r2);
        operand_read(&r3);
        operand_read(&r4);
        operand_read(&r5);
        operand_read(&r6);
        operand_read(&r7);
        cpu.edi = r0.val;
        cpu.esi = r1.val;
        cpu.ebp = r2.val;
        cpu.ebx = r4.val;
        cpu.edx = r5.val;
        cpu.ecx = r6.val;
        cpu.eax = r7.val;
    }
    print_asm_0("popa","",1);
    return len;
#else 
    printf("please implement popa\n"); assert(0);
#endif
}