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
    cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.eax);

    cpu.esp-=4;
    vaddr_write(cpu.esp,SREG_DS,4,cpu.ecx);
    
    cpu.esp-=4;
    vaddr_write(cpu.esp,SREG_DS,4,cpu.edx);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.ebx);

	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,temp_esp);
    cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.ebp);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.esi);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.edi);
    print_asm_0("pusha","",1);
    return len;
#else
     printf("please implement pusha\n"); assert(0);
#endif
}