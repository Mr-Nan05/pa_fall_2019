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

uint32_t addr_next()
{
	GateDesc *addr=(GateDesc *)(hw_mem+phy_base);
	GateDesc *addr_2=&*(addr+intr_no);
	if(addr_2->type==0xE) cpu.eflags.IF=0;

	uint32_t offset_1=addr_2->offset_15_0;
	uint32_t offset_2=addr_2->offset_31_16<<16;
	uint32_t next=offset_1 | offset_2;

	assert(addr_2->present==1);
	return next;
}

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);

	cpu_write();
	uint32_t phy_base=0;
	if(cpu.cr0.pg==1) phy_base=page_translate(cpu.idtr.base);
	else phy_base=cpu.idtr.base;


	cpu.eip=addr_next();

#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
