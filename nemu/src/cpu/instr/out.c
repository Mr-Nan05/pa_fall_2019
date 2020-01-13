#include "cpu/instr.h"
#include "device/port_io.h"

void out_write(uint32_t size)
{
    uint16_t port_addr=cpu.edx & 0xFFFF;
    size_t data_len=  size;
    uint32_t data=cpu.eax;
    pio_write(port_addr,data_len,data);
}

make_instr_func(out_b){
#ifdef HAS_DEVICE_SERIAL
    out_write(1);
    return 1;
#else
    printf("please implement out\n");assert(0);
#endif
}

make_instr_func(out_v){
#ifdef HAS_DEVICE_SERIAL
    out_write(data_size/8);
    return 1;
#else
    printf("please implement out\n");assert(0);
#endif
}