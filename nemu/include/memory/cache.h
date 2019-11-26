#ifndef __CACHE_H__
#define __CACHE_H__
#include "nemu.h"
#include "memory/mmu/segment.h"
#include "memory/mmu/page.h"
#include "memory/mmu/tlb.h"

#define group 128
#define way 8
#define line 1024

typedef struct CacheLine{
    union{
        struct{
            uint32_t validBit :1;
            uint32_t tag      :19;
            uint32_t dummy    :12;
        };
        uint32_t val;
    }flag;

    uint8_t data[64];
}CacheLine;


extern CacheLine L1_dcache[];

void init_cache();

uint32_t cache_read(paddr_t paddr,size_t len,CacheLine *cache);

void cache_write(paddr_t paddr,size_t len,uint32_t data,CacheLine *cache);

#endif
