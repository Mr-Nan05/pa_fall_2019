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

uint32_t get_ret(paddr_t paddr, size_t len)
{
	if(is_mmio(paddr)==-1){
		return hw_mem_read(paddr, len);
	}
	else{
		int map_NO = is_mmio(paddr);
		return mmio_read(paddr, len, map_NO);
	}
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
#ifndef HAS_DEVICE_VGA
#ifdef CACHE_ENABLED
	ret = cache_read(paddr,len,L1_dcache); 
#else
	ret = hw_mem_read(paddr, len);
#endif
#else
	ret = get_ret(paddr,len);
#endif
	return ret;
}

void mem_write(paddr_t paddr, size_t len, uint32_t data)
{
	if(is_mmio(paddr)==-1){
		hw_mem_write(paddr, len, data);
	}
	else{
		int map_NO = is_mmio(paddr);
		mmio_write(paddr, len, data, map_NO);
	}
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
#ifndef HAS_DEVICE_VGA
#ifdef CACHE_ENABLED
	cache_write(paddr,len,data,L1_dcache);
#else
	hw_mem_write(paddr, len, data);
#endif
#else
	mem_write(paddr,len,data);
#endif
}

bool laddr_if1()
{
	return cpu.cr0.pg && cpu.cr0.pe;
}

bool laddr_if(laddr_t laddr, size_t len)
{
	return (laddr & 0xfff) + len - 1 >= 0x1000;
}

size_t laddr_len_new(laddr_t laddr, size_t len)
{
	return len + (laddr & 0xfff) - 0x1000;
}

uint32_t laddr_laddr_new(laddr_t laddr, size_t len,size_t len_new)
{
	return  laddr + (len - len_new);
}

uint32_t laddr_read1(paddr_t paddr, paddr_t paddr_new, size_t len, size_t len_new)
{
	return (paddr_read(paddr, (len - len_new))+ (paddr_read(paddr_new, len_new) << (len - len_new)*8));
}

uint32_t laddr_read2(paddr_t paddr, size_t len)
{
	return paddr_read(paddr, len);
}

uint32_t laddr_read3(laddr_t laddr, size_t len)
{
	return	paddr_read(laddr,  len);
}

void laddr_assert(size_t len)
{
	assert(len == 1||len == 2 || len == 4);
}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
	//return paddr_read(laddr, len);

	laddr_assert(len);
	if(laddr_if1()){
		if(laddr_if(laddr, len)){
			size_t len_new = laddr_len_new(laddr, len);
			uint32_t laddr_new = laddr_laddr_new(laddr, len, len_new);
			paddr_t paddr = page_translate(laddr);
			paddr_t paddr_new = page_translate(laddr_new);
			return laddr_read1(paddr, paddr_new, len, len_new);

		}
		else {
			paddr_t paddr = page_translate(laddr);
			return laddr_read2(paddr,len);
		}
	}
	else return laddr_read3(laddr, len);
}



void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
	laddr_assert(len);
	if(laddr_if1()){
		if(laddr_if(laddr, len)){
			size_t len_new = laddr_len_new(laddr, len);
			uint32_t laddr_new = laddr_laddr_new(laddr, len, len_new);
			paddr_t paddr = page_translate(laddr);
			paddr_t paddr_new = page_translate(laddr_new);
		
			uint32_t data_tmp2 = data >> ((len - len_new)*8);
			uint32_t data_tmp1 = data - (data_tmp2 << (len - len_new)*8);

			//data_tmp2 = data >> ((len - len_new)*8);
			//data_tmp1 = data - (data_tmp2 << (len - len_new)*8);

			paddr_write(paddr,(len - len_new),data_tmp1);
			paddr_write(paddr_new, len_new, data_tmp2);
		}
		else {
			paddr_t paddr = page_translate(laddr);
			paddr_write(paddr,len,data);
		}
	}

	else paddr_write(laddr, len, data);
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len)
{
	laddr_assert(len);
	uint32_t laddr = vaddr;
	if(cpu.cr0.pe){
		laddr = segment_translate(vaddr,sreg);
	}
	return laddr_read(laddr,len);
	//return laddr_read(vaddr, len);
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	laddr_assert(len);
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
	laddr_assert(len);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr()
{
	return hw_mem;
}
