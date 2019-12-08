#include "cpu/cpu.h"
#include "memory/memory.h"
//#include "cpu/reg.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	return cpu.segReg[sreg].base + offset;
}

void load_sreg_assert(SegDesc target)
{
	assert(target.privilege_level >= cpu.segReg[sreg].rpl);
	assert(target.present == 1);
	assert(target.granularity == 1);
	assert(target.base_15_0 == 0);
	assert(target.base_23_16 == 0);
	assert(target.base_31_24 == 0);

	assert(target.limit_15_0 == 0xffff);
	assert(target.limit_19_16 == 0xf);
}



// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	SegDesc target;
	uint32_t entry = cpu.gdtr.base + (cpu.segReg[sreg].index) * 8;

	target.val[0] = laddr_read(entry, 4);
	target.val[1] = laddr_read(entry + 4, 4);

	load_sreg_assert(target);

	cpu.segReg[sreg].base = target.base_15_0 + ((uint32_t)target.base_23_16 << 16) + ((uint32_t)target.base_31_24 << 24);
	cpu.segReg[sreg].limit = target.limit_15_0 + ((uint32_t)target.limit_19_16 << 16);
	cpu.segReg[sreg].soft_use = target.soft_use;
	cpu.segReg[sreg].privilege_level = target.privilege_level;
	cpu.segReg[sreg].type = target.type + (target.segment_type << 4);
}
