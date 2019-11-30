#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	//printf("\nPlease implement page_translate()\n");
	//assert(0);

	paddr_t result = 0;
	uint32_t offset = (laddr & 0xfff);
	uint32_t page = ((laddr>>12) & 0x3ff);
	uint32_t dir = ((laddr>>22) & 0x3ff);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
