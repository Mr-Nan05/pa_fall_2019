#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include "memory/cache.h"
#include <stdio.h>

uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data)
{
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
uint32_t ret = 0;
#ifdef CACHE_ENABLED
ret = cache_read(paddr, len, L1_dcache);
#else
ret = hw_mem_read(paddr, len);
#endif
return ret;
}
void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
#ifdef CACHE_ENABLED
cache_write(paddr, len, data, L1_dcache);
#else
hw_mem_write(paddr, len, data);
#endif
}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
	//return paddr_read(laddr, len);

	assert(len == 1||len == 2 || len == 4);
	if(cpu.cr0.pg && cpu.cr0.pe){
		if((laddr & 0xfff) + len - 1 >= 0x1000){
			size_t len_new = len + (laddr & 0xfff) - 0x1000;
			uint32_t laddr_new = laddr + (len - len_new);
			paddr_t paddr = page_translate(laddr);
			paddr_t paddr_new = page_translate(laddr_new);
			return (paddr_read(paddr, (len - len_new) + (paddr_new, len_new) << (len - len_new)*8));

		}
		else {
			paddr_t paddr = page_translate(laddr);
		}
	}
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
	paddr_write(laddr, len, data);
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	uint32_t laddr = vaddr;
	if(cpu.cr0.pe){
		laddr = segment_translate(vaddr,sreg);
	}
	return laddr_read(laddr,len);
	//return laddr_read(vaddr, len);
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
	uint32_t laddr=vaddr;
	if(cpu.cr0.pe){
		laddr = segment_translate(vaddr,sreg);
	}
	laddr_write(laddr,len,data);
	//laddr_write(vaddr, len, data);
}

void init_mem()
{
	// clear the memory on initiation
#ifdef CACHE_ENABLED
			init_cache();
#endif
	memset(hw_mem, 0, MEM_SIZE_B);

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr()
{
	return hw_mem;
}
