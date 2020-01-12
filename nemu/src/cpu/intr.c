#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void cpu_write()
{
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.eflags.val);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.cs.val);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_DS,4,cpu.eip);
}

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);

	cpu_write();

#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
