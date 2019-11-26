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