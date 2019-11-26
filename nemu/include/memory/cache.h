#ifdef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"
#include "memory/mmu/segment.h"
#include "memory/mmu/page.h"
#include "memory/mmu/tlb.h"

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



#endif