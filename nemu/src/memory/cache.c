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

    while(count < way){
        if((cache[lineNO+count].flag.tag==mark) && (cache[lineNO+count].flag.validBit)){
            if(len+blockAddress-1<64){
                for(int i=blockAddress;i<(len+blockAddress);i++){
                        ret+=(((uint32_t)cache[lineNO+count].data[i])<<((i-blockAddress)*8));
                    }
                }
            else{
                size_t len_new=len+blockAddress-64;
                uint32_t paddr_new=paddr+(len-len_new);
                for(int i=blockAddress;i<64;i++){
                    ret+=(((uint32_t)cache[lineNO+count].data[i])<<((i-blockAddress)*8));
                }
                ret+=(cache_read(paddr_new,len_new,cache)<<((len-len_new)*8));
            }
            hit_judge=true;
            break;
        }
        count++;
    }

     if(hit_judge==true) return ret;
     else {
           uint32_t num=0;
           num=rand()%way;

           cache[lineNO+num].flag.validBit=1;
           cache[lineNO+num].flag.tag=mark;

           uint32_t paddr_new=((paddr>>6)<<6);

           for(int i=0;i<64;i++)
           cache[lineNO+num].data[i]=hw_mem[paddr_new+i];

           ret = cache_read(paddr,len,cache);
           return ret;

     }

}


void cache_write(paddr_t paddr,size_t len,uint32_t data,CacheLine *cache){

    uint32_t blockAddress = paddr & 0x3f;
    uint32_t groupNO = (paddr>>6) & 0x7f;
    uint32_t mark = (paddr>>13) & 0x7ffff;

    uint32_t data_tmp = data;
    


}

