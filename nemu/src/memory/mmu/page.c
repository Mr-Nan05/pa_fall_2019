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


	PDE pde_target;
	paddr_t pdir_base = cpu.cr3.pdbr << 12;
	pde_target.val = paddr_read(pdir_base + dir*4, 4);

	assert(pde_target.present == 1);

	PTE pte_target;
	paddr_t pt_base = pde_target.page_frame << 12;
	pte_target.val = paddr_read(pt_base + page*4, 4);

	assert(pte_target.present == 1);

	result = (pte_target.page_frame << 12) + offset;

	return result;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
