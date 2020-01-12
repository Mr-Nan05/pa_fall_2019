#include "cpu/instr.h"

void cpu_write()
{
    cpu.eip=vaddr_read(cpu.esp,SREG_DS,4);
	cpu.esp+=4;
    cpu.cs.val=vaddr_read(cpu.esp,SREG_DS,4);
	cpu.esp+=4;
    cpu.eflags.val=vaddr_read(cpu.esp,SREG_DS,4);
	cpu.esp+=4;
}
make_instr_func(iret){
#ifdef IA32_INTR
    cpu_write();
    return 0;
#else
    printf("please implement iret\n"); assert(0);
#endif
}