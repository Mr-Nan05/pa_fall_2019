#ifdef __CACHE_H__
#define __CACHE_H__



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