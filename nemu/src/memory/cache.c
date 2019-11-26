#include "nemu.h"
#include"cpu/cpu.h"
#include "memory/memory.h"
#include "memory/cache.h"
#include <stdio.h>
#include <stdlib.h>

CacheLine L1_dcache[line];

void init_cache(){
    for(int i=0;i<line;i++){
        L1_dcache[i].flag.validBit=0;
        L1_dcache[i].flag.tag=0;
        for(int j=0;j<64;j++)
            L1_dcache[i].data[j]=0;
    }
}

uint32_t cache_read(paddr_t paddr,size_t len,CacheLine *cache){

    uint32_t ret=0;
    uint32_t blockAddress = paddr & 0x3f;
    uint32_t groupNO = (paddr>>6) & 0x7f;
    uint32_t mark = (paddr>>13) & 0x7ffff;

    uint32_t lineNO=groupNO*way;
    uint32_t count=0;
    bool hit_judge=false;

}


void cache_write(paddr_t paddr,size_t len,uint32_t data,CacheLine *cache){




}

